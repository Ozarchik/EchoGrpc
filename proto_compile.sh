#! /bin/bash

protoc -I proto \
	--cpp_out=src \
	--grpc_out=src \
	--plugin=protoc-gen-grpc=`which grpc_cpp_plugin` \
	proto/echo.proto
