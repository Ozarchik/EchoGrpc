cmake_minimum_required(VERSION 3.16)
project(echo_grpc)

find_package(gRPC REQUIRED)
find_package(Protobuf REQUIRED)

add_executable(server
	src/server.cpp
	src/echo.pb.cc
	src/echo.grpc.pb.cc
)
target_link_libraries(server
	gRPC::grpc++
	protobuf::libprotobuf
)

add_executable(client
	src/client.cpp
	src/echo.pb.cc
	src/echo.grpc.pb.cc
)
target_link_libraries(client
	gRPC::grpc++
	protobuf::libprotobuf
)



