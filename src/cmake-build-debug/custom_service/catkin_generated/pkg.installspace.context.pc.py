# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include".split(';') if "${prefix}/include" != "" else []
PROJECT_CATKIN_DEPENDS = "message_generation;message_runtime;roscpp".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-lcustom_service".split(';') if "-lcustom_service" != "" else []
PROJECT_NAME = "custom_service"
PROJECT_SPACE_DIR = "/usr/local"
PROJECT_VERSION = "0.0.0"
