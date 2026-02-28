#include <iostream>
#include <string>
#include <memory>

#include <grpcpp/grpcpp.h>
#include "echo.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using echo::EchoService;
using echo::EchoRequest;
using echo::EchoReply;

class EchoServiceImpl final: public EchoService::Service
{
public:
	Status Echo(
		ServerContext* context,
		const EchoRequest* request,
		EchoReply* reply	
	) override {
		std::cout << "Request: " << request->message() << std::endl;
		reply->set_message("Server OK: " + request->message());
		return Status::OK;
	}
};

void RunServer()
{
	std::string address("0.0.0.0:50051");
	EchoServiceImpl service;
	ServerBuilder builder;
	builder.AddListeningPort(address, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	std::unique_ptr<Server> server(builder.BuildAndStart());
	
	std::cout << "Server start listening on " <<  address << std::endl;
	server->Wait();
}


int main()
{
	RunServer();
	return 0;
}
