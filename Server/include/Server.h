#pragma once
#include "NetCommon.h"
#include "NetQueue.h"
#include "NetPacket.h"
#include "NetTCPConnection.h"
#include "NetServerApp.h"

class World;
class Character;

namespace NetLib {
	class Server : public ServerApp<CMD> {
	public:
		Server(uint16_t port);
		~Server();

	protected:
		virtual bool OnClientConnect(std::shared_ptr<TCPConnection<CMD>>& client) override {
			Packet<CMD> pkt;
			pkt.header.cmdID = CMD::AcceptTCPConnection;
			SendToClient(client, pkt);
			return true;
		}
		virtual void OnClientDisconnect(std::shared_ptr<TCPConnection<CMD>>& client) override;
		virtual void OnPacket(std::shared_ptr<TCPConnection<CMD>>& client, Packet<CMD>& pkt) override;
		

	private:
		std::shared_ptr<World>        m_World;

	protected:
		std::mutex						m_mux;
		std::condition_variable			m_cvBlock;
		std::mutex						m_muxBlock;

	};
}