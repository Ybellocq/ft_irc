#include "Channel.hpp"

Channel::Channel(const std::string& name)
        : _name(name), _password(""), _topic(""), _inviteOnly(false),
          _restrictTopic(true), _limitUser(false), _passwordUse(false),
          _nUser(0) {}


void Channel::sendMessage(Client* client, const std::string& msg) {
    send(client->getFd(), msg.c_str(), msg.size(), MSG_CONFIRM);
}

void Channel::createChannel(const std::string& name, Client* creator) {
    Channel channel(name);

    channel._operators[creator->getNickname()] = creator;
    channel._regulars[creator->getNickname()] = creator;

    std::string joinMsg = ":" + creator->getNickname() + "!~" + creator->getUsername()[0] + "@127.0.0.1 JOIN #" + name + "\n";
    sendMessage(creator, joinMsg);

    std::string modeMsg = ":127.0.0.1 MODE #" + name + " +nt\n";
    sendMessage(creator, modeMsg);

    std::string namesMsg = ":127.0.0.1 353 " + creator->getNickname() + " = #" + channel._name + " :@" + creator->getNickname() + "\n";
    sendMessage(creator, namesMsg);

    std::string endNamesMsg = ":127.0.0.1 366 " + creator->getNickname() + " #" + name + " :End of /NAMES list.\n";
    sendMessage(creator, endNamesMsg);
}

const std::string& Channel::getName() const {
    return (_name);
}

Channel::~Channel(){

}