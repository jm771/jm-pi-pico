BUILD_DIR:=build
PROJECT_NAME:=midi_controller
SRC:=$(wildcard *.c) $(wildcard *.h)

.PHONY: setup bin

${BUILD_DIR}: CMakeLists.txt
	mkdir -p ${BUILD_DIR}
	PROJECT_NAME=${PROJECT_NAME} cmake -S . ${BUILD_DIR}

setup: ${BUILD_DIR}

bin: setup ${SRC}
	PROJECT_NAME=${PROJECT_NAME} cmake --build ${BUILD_DIR} --target ${PROJECT_NAME}

clean:
	yes | rm -rf ${BUILD_DIR}
