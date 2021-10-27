from conans import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake
from conan.tools.layout import cmake_layout


class BinancesdkConan(ConanFile):
    name = "binancesdk"
    version = "0.1"
    # Optional metadata
    license = "MIT"
    author = "<Put your name here> <And your email here>"
    url = ""
    description = ""
    topics = ("binance", "trading")
    generators = "cmake_paths", "cmake_find_package"
    install_folder = "build"
    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": True, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*"

    def requirements(self):
        self.requires("openssl/1.1.1l")
        self.requires("gtest/1.11.0")
        self.requires("boost/1.77.0")
        # self.requires("date/3.0.1")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        if not self.settings.os == "Windows":
            self.settings.compiler = "gcc"
            self.settings.compiler.version = "10.3"
            self.settings.compiler.libcxx = "libstdc++11"
            self.cpp_info.cxxflag = [
                "-fsanitize=address", "-fno-omit-frame-pointer"]

        self.cpp_info.libs = ["binancesdk"]
