#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "echo.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using echo::EchoService;
using echo::EchoRequest;
using echo::EchoReply;

class EchoClient {
public:
	EchoClient(std::shared_ptr<Channel> channel)
	: m_stub(EchoService::NewStub(channel))
	{
	}
	
	std::string Echo(const std::string& message)
	{
		EchoRequest request;
		request.set_message(message);

		ClientContext context;
		EchoReply reply;

		Status status = m_stub->Echo(&context, request, &reply);

		if (status.ok()) {
			return reply.message();	
		} else {
			std::cerr << "RPC Failed: "
					  << status.error_message()
					  << std::endl;
			return {};
		}
	}

private:
	std::unique_ptr<EchoService::Stub> m_stub;
};


int main()
{
	std::string address("localhost:50051");

	EchoClient client(
		grpc::CreateChannel(
			address,
			grpc::InsecureChannelCredentials()
		)
	);

	std::string response = client.Echo("Hello, im grpc client");
	std::cout << "Server replied: " << response << std::endl;

	return 0;
}
