# Description of the socket communication

## Generalities

A message begins by the byte ';' and ends with the byte '\n'

## List of messages

- **SERVER -> CLIENT** `;lvl <start_now> <nrow> <ncol> <npieces> <desc>\n` 
  - Send the layout of the level during the setup phase
  - start_now: 1 if the player will be the first one to play
  - nrow: the number of rows of the level
  - ncol: the number of columns of the level
  - npieces: the number of pieces on board (Red+Blue). Using to check for next field
  - desc: a concatenation of blocks `<row> <col> <clr> <type> <orientation>` spaced with spaces characters
    - row, col: position of the piece
    - clr: color of the piece
      - 0: Blue
      - 1: Red
    - type: type of piece at this position
      - L: laser piece
      - M: deflector (piece with only one miror, oriented at 45°)
      - D: Defender (piece with only one mirror, oriented at 0°)
      - S: Switch (piece with two miror, orientated at 45°)
      - K: King
    - orientation: char describing the orientation (some piece are facing at 45°)
      - 0: N or NE
      - 1: E or SE
      - 2: S or SW
      - 3: W or NW
- **CLIENT -> SERVER** `;lvlerror\n`
  - If the `lvl` message has a parsing error.
  - Client and server should close sockets on this message
- **SERVER -> CLIENT** `;yourturn\n`
  - Sent by the server to the client when it's its turn
- **SERVER -> CLIENT** `;won\n` and `;lost\n`
  - To indicate the end of the game and whether the client has won or lost
  - Client and server should close socket on this message
- **CLIENT -> SERVER** `;move <row> <col> <new_row> <new_col>\n`
  - row, col are the original position of the piece
  - new_row, new_col are the new position for this piece
- **CLIENT -> SERVER** `;rot <row> <col> <rot>\n`
  - row, col are the position of the piece
  - rot: +1 if clockwise rotation, -1 if anti-clockwise rotation
- **SERVER -> CLIENT** `;action valid\n` 
  - if sent action is accepted or 
- **SERVER -> CLIENT** `;action invalid\n` 
  - if the action is invalid (does not respect rules).