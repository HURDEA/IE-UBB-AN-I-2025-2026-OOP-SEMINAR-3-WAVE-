#pragma once
#include <string>
#include <ostream>
enum class Priority { LOW, NORMAL, IMPORTANT };
class Transmission {
	/*id(int) - A unique identifier.

	sender(std::string) - – The name of the sending operator or station.

		receiver(std::string) - The name of the receiving operator or station.

		content(std::string) - The actual message text.

		priority(enum class) - The priority of the message(LOW, NORMAL, IMPORTANT)
		*/
	
	int id;
	std::string sender;
	std::string receiver;
	std::string content;
	Priority priority;
	int static STATIC_ID;
	//Transmision() : id(STATIC_ID++), sender(""), receiver(""), content(""), priority(Priority::NORMAL) {}
public:
	Transmission(std::string sender, std::string receiver, std::string content, Priority priority) : id(STATIC_ID++), sender(sender), receiver(receiver), content(content), priority(priority) {}
	std::string getSender() { return sender; }
	std::string getReceiver() { return receiver; }
	std::string getContent() { return content; }
	Priority getPriority() { return priority; }
	friend std::ostream& operator<<(std::ostream & os, const Transmission& t) {
		os << "ID: " << t.id << "\nSender: " << t.sender << "\nReceiver: " << t.receiver << "\nContent: " << t.content << "\nPriority: ";
		switch (t.priority) {
		case Priority::LOW:
			os << "LOW";
			break;
		case Priority::NORMAL:
			os << "NORMAL";
			break;
		case Priority::IMPORTANT:
			os << "IMPORTANT";
			break;
		}
		return os;

	}
	int getId() const { return id; }
	
};

