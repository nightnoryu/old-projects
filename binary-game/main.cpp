#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>


// Generates random number between 0 and 255 (1 byte)
int random_number();

int dec_to_bin(int number);


int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Choose game mode (0 - dec to bin; 1 - bin to dec)" << std::endl;
    return 1;
  }

  bool game_mode = atoi(argv[1]);
  bool game_over = 0;
  int score = 0, lives = 3;
  int number, answer, user_input;

  // Init random numbers
  srand(time(NULL));

  // Game loop
  while (!game_over) {
    if (!game_mode) {          // Dec to bin
      // Greet player
      std::cout << "Numbers in decimal will appear on the screen. Write them in binary. You have 3 lives." << std::endl;
      number = random_number();
      answer = dec_to_bin(number);
      std::cout << number << " (10) = ";
    } else {                  // Bin to dec
      std::cout << "Numbers in binary will appear on the screen. Write them in decimal. You have 3 lives." << std::endl;
      answer = random_number();
      number = dec_to_bin(answer);
      std::cout << number << " (2) = ";
    }
    std::cin >> user_input;
    if (answer == user_input) {
      ++score;
      std::cout << "Yeah. Good." << std::endl;
    }
    else {
      --lives;
      std::cout << "Incorrect. The right answer is " << answer << std::endl;
      std::cout << lives << " live" << (lives == 1 ? "" : "s") << " left.\n" << std::endl;
      if (lives <= 0) {
        std::cout << "Game over!\nYour score is " << score << std::endl;
        game_over = 1;
      }
    }
  }

  return 0;
}


int random_number() {
  int number = rand() % 256;
  return number;
}

int dec_to_bin(int number) {
  int result = 0;
  for (int i = 0; number > 0; ++i) {
    result += (number % 2) * pow(10, i);
    number /= 2;
  }
  return result;
}
