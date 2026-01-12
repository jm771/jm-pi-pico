BUILD_DIR:=build
PROJECT_NAME:=hat_controller
SRC:=$(wildcard *.c) $(wildcard *.h)

.PHONY: setup bin

bin: setup ${SRC}
	cmake --build ${BUILD_DIR} --target ${PROJECT_NAME}

${BUILD_DIR}: CMakeLists.txt
	mkdir -p ${BUILD_DIR}
	cmake -S . ${BUILD_DIR}

setup: ${BUILD_DIR}

clean:
	yes | rm -rf ${BUILD_DIR}


deploy: bin
	./deploy.sh
