#include "common/args/parser.hpp"
#include "common/game/board.hpp"
#include "common/game/messages.hpp"
#include "common/game/pieces/piece.hpp"
#include "common/math/vector.hpp"
#include "common/socket/socket.hpp"

using laser::args::ArgumentParser;
using laser::com::Messages;
using laser::com::Socket;
using laser::game::Board;
using laser::game::PieceColor;

bool StayConnected = true;

ArgumentParser make_parser() {
  auto parser = ArgumentParser();
  parser.add_arg("--port");
  parser.add_arg("--ip");
  return parser;
}

void MessageParser(Messages clientMessage);

int main(int argc, char **argv) {
  // Argument parsing
  auto parser = make_parser();
  parser.parse_args(argc, argv);
  parser.display_args();

  auto ip = parser.get<std::string>("--ip", "127.0.0.1");
  auto port = parser.get<int>("--port", 5001);

  std::cout << "Initializing AI client with server (" << ip << ":" << port << ")" << std::endl;

  Board board = Board();
  board.CreateDefaultBoard();
  for (int i = 0; i < 10; i++) {
    FindBestMove(PieceColor::BLUE, board);
  }

  auto sock = Socket(ip, port);
  if (sock.connectToServer()) {
    while (StayConnected) {
      std::cout << "Waiting for message" << std::endl;
      std::string output;
      sock.receive_data(output);
      std::cout << "Received from server msg: (" << output << ")" << std::endl;
      Messages ClientMessage = laser::com::getMessage(output);
      MessageParser(ClientMessage);
    }
    // std::cout << "Sending message" << std::endl;
    // sock.send_data(";clientmsg\n");
  } else {
    std::cout << "Couldn't connect to server" << std::endl;
  }

  return 0;
}

void MessageParser(Messages clientMessage) {
  switch (clientMessage) {
    case Messages::YOUR_TURN: {
      std::cout << "YOUR TURN MESSAGE RECEIVED." << std::endl;
      break;
    }

    case Messages::WON_GAME: {
      std::cout << "WON GAME MESSAGE RECEIVED." << std::endl;
      break;
    }

    case Messages::LOST_GAME: {
      std::cout << "LOST GAME MESSAGE RECEIVED." << std::endl;
      break;
    }

    case Messages::ACTION_VALID: {
      std::cout << "ACTION VALID MESSAGE RECEIVED." << std::endl;
      break;
    }

    case Messages::ACTION_INVALID: {
      std::cout << "ACTION INVALID MESSAGE RECEIVED." << std::endl;
      break;
    }

    default: {
      std::cout << "Message not understood." << std::endl;
      break;
    }
  }
}