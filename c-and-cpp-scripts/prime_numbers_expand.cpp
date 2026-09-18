/*
 * This program calculates the prime number expansion of a number
 */
#include <iostream>
#include <vector>
#include <string>

// Functions for the data input
int get_number_from_args(char **argv);
int get_number_from_stdin();

// Returns true if the number is prime
bool is_prime(int number);

// Returns first primes_size prime numbers vector
std::vector<bool> get_primes(std::vector<bool>::size_type primes_size);

// Returns a vector prime expansion of a number
std::vector<int> get_expansion(int number, std::vector<bool> &primes);

// Prints the result in a nice form
void print_result(int number, std::vector<int> &result);


int main(int argc, char **argv)
{
  int number;

  // Get the number either from arguments, or from stdin
  if (argc > 1) {
    number = get_number_from_args(argv);
    if (number == -1)
      number = get_number_from_stdin();
  } else {
    number = get_number_from_stdin();
  }

  // Check if the number is already prime
  if (is_prime(number)) {
    std::cout << number << " is prime." << std::endl;
    return 0;
  }

  // Get and print the result
  std::vector<bool> primes = get_primes(number);
  std::vector<int> result = get_expansion(number, primes);
  print_result(number, result);
  std::cout << std::endl;
}


int get_number_from_args(char **argv)
{
  int number = -1;
  std::string param = argv[1];

  try {
    number = std::stoi(param, nullptr, 10);
    if (number < 1)
      throw std::exception();

  } catch (const std::exception& e) {
    std::cerr << "Invalid parameter: " << param << "\n";
    number = -1;
  }

  return number;
}

int get_number_from_stdin()
{
  int number;

  do {
    std::cout << "Enter a positive number: ";
    std::cin >> number;

    if (std::cin.fail()) {
      std::cerr << "Invalid input, please try again\n";
      std::cin.clear();
      std::cin.ignore(256, '\n');
      number = -1;
    } else if (number < 1) {
      std::cerr << "Invalid input, the number must be positive\n";
    }
  } while (number < 1);

  return number;
}

bool is_prime(int number)
{
  for (int i = 2; i * i <= number; i++)
    if (number % i == 0)
      return false;
  return true;
}

std::vector<bool> get_primes(std::vector<bool>::size_type primes_size) {
  // Get the primes, using the sieve of Eratosthenes
  std::vector<bool> primes(primes_size, true);
  primes[0] = primes[1] = false;

  for (int i = 2; i <= primes_size; i++) {
    if (primes[i]) {
      for (int j = i * i; j <= primes_size; j += i) {
        primes[j] = false;
      }
    }
  }
  return primes;
}

std::vector<int> get_expansion(int n, std::vector<bool> &p) {
  std::vector<int> exp;
  // Iterate & divide until number becomes zero
  while (n > 1) {
    // Go through the primes to find the ones that divide properly
    for (int i = p.size(); i > 1; i--) {
      if (p[i] && n % i == 0) {
        n /= i;
        exp.push_back(i);
        break;
      }
    }
  }
  return exp;
}

void print_result(int number, std::vector<int> &result)
{
  std::cout << number << " = " << result[0];
  typedef std::vector<int>::const_iterator VI;
  for (VI i = result.begin() + 1; i != result.end(); i++) {
    std::cout << " * " << *i;
  }
}
