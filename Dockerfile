FROM ubuntu:24.04 AS builder

RUN apt update && apt install -y \
	build-essential \
	cmake \
	git \
	pkg-config \
	protobuf-compiler \
	libprotobuf-dev \
	libgrpc++-dev \
	protobuf-compiler \
	protobuf-compiler-grpc

WORKDIR /app

COPY . .

RUN cmake -S . -B build && cmake --build build

FROM ubuntu:24.04

RUN apt update && apt install -y \
	libprotobuf-dev \
	libgrpc++-dev

WORKDIR /app

COPY --from=builder /app/build/server .

EXPOSE 50051

CMD ["./server"]

