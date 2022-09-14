import os

from conans import ConanFile


os.environ["CONAN_CMAKE_GENERATOR"] = "Ninja"


class NNCCConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        "double-conversion/3.2.0",
        "entt/3.10.1",
        "gflags/2.2.2",
        "glfw/3.3.7",
        "folly/2022.01.31.00",
        "imgui/cci.20220621+1.88.docking",
        "libiconv/1.17",
        "mpdecimal/2.5.1",
        "openssl/1.1.1q",
        "zlib/1.2.12"
    ]
    generators = "CMakeToolchain", "CMakeDeps", "cmake"
    default_options = {
        "folly:shared": False
    }
