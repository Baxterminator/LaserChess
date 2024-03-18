#include "common/args/parser.hpp"
#include "common/socket/socket.hpp"
#include "ai/ClientMessageParser.hpp"
#include "ai/Board.hpp"
#include "ai/Vector.hpp"
#include "common/socket/errors.hpp"
using laser::args::ArgumentParser;
using laser::com::Socket;

bool StayConnected = true;

typedef enum ClientStates_tag {
  WAIT_FOR_TURN, //
  COMPUTE_MOVE, //Computes a move to perform
  // WAIT_FOR_ACK,
  // APPLY_MOVE, //;action valid\n received, apply move to internal boardstate
  APPLY_PLAYER_MOVE, //Applies the human players move to internal boardstate
  WON_LOST, //Game is over, close connection and program
} ClientStates_t;

static ClientStates_t clientState = WAIT_FOR_TURN;

static Board boardState = Board();

auto sock = Socket("127.0.0.1", 5001);

static void ClientStateMachine(void);

ArgumentParser make_parser() {
  auto parser = ArgumentParser();
  parser.add_arg("--port");
  parser.add_arg("--ip");
  return parser;
}

void MessageParser(ClientMessages_t clientMessage, std::string message);

int main(int argc, char **argv) {
  // Argument parsing
  auto parser = make_parser();
  parser.parse_args(argc, argv);
  parser.display_args();

  boardState.CreateDefaultBoard();
  // StringToMove(";move 5 5 3 9\n", boardState);


  if (sock.connectToServer()) {
    while (StayConnected) {
      std::cout << "Waiting for message" << std::endl;
      std::string output;
      sock.receive_data(output);
      std::cout << "Received from server msg: (" << output << ")" << std::endl;
      ClientMessages_t ClientMessage = ClientMessageParser(output);
      MessageParser(ClientMessage, output);

    }
    // std::cout << "Sending message" << std::endl;
    // sock.send_data(";clientmsg\n");
  } else {
    std::cout << "Couldn't connect to server" << std::endl;
  }

  return 0;
}


static void ClientStateMachine(void)
{
  switch (clientState)
  {
    case WAIT_FOR_TURN:
    {
      //do nothing, wait for turn
      break;
    }

    case COMPUTE_MOVE:
    {
      std::string moveString = FindBestMove(BLUE, boardState);
      if (sock.send_data(moveString) == laser::com::SocketErrors::NO_ERROR1) {
        // clientState = WAIT_FOR_ACK;
      }
      break;
    }

    // case WAIT_FOR_ACK:
    // {
    //   break;
    // }

    // case APPLY_MOVE:
    // {
    //   break;
    // }

    case APPLY_PLAYER_MOVE:
    {
      break;
    }
  }
}


void MessageParser(ClientMessages_t clientMessage, std::string message)
{
  switch(clientMessage)
  {
    case YOUR_TURN:
    {
      std::cout << "YOUR TURN MESSAGE RECEIVED." << std::endl;
      if (clientState == WAIT_FOR_TURN) {
        clientState = COMPUTE_MOVE;
        ClientStateMachine();
      }
      break;
    }

    case WON_GAME:
    {
      std::cout << "WON GAME MESSAGE RECEIVED." << std::endl;
      break;
    }

    case LOST_GAME:
    {
      std::cout << "LOST GAME MESSAGE RECEIVED." << std::endl;
      break;
    }

    case ACTION_VALID:
    {
      std::cout << "ACTION VALID MESSAGE RECEIVED." << std::endl;
      // if (clientState == WAIT_FOR_ACK) {
      //   clientState = APPLY_MOVE;
      // }
      break;
    }

    case ACTION_INVALID:
    {
      std::cout << "ACTION INVALID MESSAGE RECEIVED." << std::endl;
      break;
    }

    case MOVE_STRING:
    {
      std::cout << "MOVE COMMAND RECEIVED FROM SERVER. " << std::endl;
      StringToMove(message, boardState);
      break;
    }

    default:
    {
      std::cout << "Message not understood." << std::endl;
      break;
    }
  }
}