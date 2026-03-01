# Echo gRPC

<div align="center">

**A minimal gRPC service in C++**

[![CI](https://github.com/Ozarchik/EchoGrpc/actions/workflows/ci.yml/badge.svg)](https://github.com/Ozarchik/EchoGrpc/actions/workflows/ci.yml)
[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![gRPC](https://img.shields.io/badge/gRPC-1.x-green.svg)](https://grpc.io/)
[![CMake](https://img.shields.io/badge/CMake-3.16+-purple.svg)](https://cmake.org/)
[![Docker](https://img.shields.io/badge/Docker-Ready-2496ED.svg)](https://www.docker.com/)

</div>

---

## 📖 Description

Echo gRPC is a minimal example of a gRPC application in C++, demonstrating client–server communication via Protocol Buffers. The service accepts a string message and returns it with a confirmation prefix.

### Features

- **Echo service** — single RPC method `Echo` that accepts a message and returns a response
- **CMake build** — standard configuration for C++ projects
- **Docker** — images for both server and client
- **Protocol Buffers** — API definition in `proto/echo.proto`

---

## 🏗 Project Structure

```
EchoGrpc/
├── proto/
│   └── echo.proto          # gRPC service definition
├── src/
│   ├── server.cpp          # gRPC server
│   ├── client.cpp          # gRPC client
│   ├── echo.pb.cc/h        # Generated protobuf code
│   └── echo.grpc.pb.cc/h   # Generated gRPC code
├── CMakeLists.txt
├── build.sh                # Build script
├── proto_compile.sh        # Code generation from .proto
├── .github/workflows/
│   └── ci.yml              # CI/CD pipeline
├── Dockerfile
└── README.md
```

---

## ⚙️ Requirements

- **CMake** ≥ 3.16
- **gRPC** and **Protocol Buffers** (C++)
- **C++17** or newer

### Installing dependencies (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install -y build-essential cmake pkg-config \
    protobuf-compiler libprotobuf-dev libgrpc++-dev protobuf-compiler-grpc
```

---

## 🚀 Build

### 1. Generate code from proto

First, generate C++ code from the `.proto` file:

```bash
./proto_compile.sh
```

This creates `echo.pb.cc`, `echo.pb.h`, `echo.grpc.pb.cc`, and `echo.grpc.pb.h` in `src/`.

### 2. Build the project

```bash
./build.sh
```

Or manually:

```bash
cmake -S . -B build
cmake --build build
```

Executables will be in `build/`:
- `build/server` — gRPC server
- `build/client` — gRPC client

---

## 🐳 Docker

> ⚠️ Run `./proto_compile.sh` before building Docker images — the generated `.pb.cc` and `.pb.h` files must be present in `src/`.

### Build images

```bash
# Server
docker build --target server -t echo-grpc-server .

# Client
docker build --target client -t echo-grpc-client .
```

### Run

**Terminal 1 — server:**
```bash
docker run -p 50051:50051 echo-grpc-server
```

**Terminal 2 — client:**
```bash
docker run --network host echo-grpc-client
```

> Use `--network host` or Docker Compose with a shared network to connect containers.

---

## 📡 Usage

### Local run

**1. Start the server:**
```bash
./build/server
```

The server listens on port `50051`.

**2. In another terminal, run the client:**
```bash
./build/client
```

Example client output:
```
Server replied: Server OK: Hello, im grpc client
```

---

## 📋 API

### Echo

| Parameter | Type         | Description                    |
|-----------|--------------|--------------------------------|
| Request   | `EchoRequest`| `message: string` — text to echo |
| Response  | `EchoReply`  | `message: string` — server response |

**Example:** request `"Hello"` → response `"Server OK: Hello"`.

---

## 📄 License

Provided as-is for educational purposes.
