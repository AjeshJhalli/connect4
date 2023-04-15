#include <iostream>

#define GRID_WIDTH 8
#define GRID_HEIGHT 8

char grid[GRID_WIDTH * GRID_HEIGHT];
	
void setup_grid();
void display_grid();
void player_turn(char);
bool four_in_a_row(char);
bool grid_is_full();
void clear_screen();

int main()
{
	char player = '1';
		
	setup_grid();
	clear_screen();
	
	while(true)
	{
		display_grid();
		player_turn(player);
		
		if(four_in_a_row(player))
		{
			clear_screen();
			display_grid();
			std::cout << "Player " << player << " has won!" << std::endl;
			break;
		}
		else if(grid_is_full())
		{
			clear_screen();
			display_grid();
			std::cout << "It is a draw." << std::endl;
			break;
		}

		player = player == '1' ? '2' : '1';

		clear_screen();
	}
	
	std::cin.get();
	std::cin.get();
	
	return 0;
}

void setup_grid()
{
	for(int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++)
		grid[i] = '0';
}

void display_grid()
{
	std::cout << "\nEnter a column number to put a piece into that column.\n\n";

	if (GRID_WIDTH < 10)
	{
		for(int x = 1; x < GRID_WIDTH + 1; x++)
		{
			std::cout << x << " ";
		}

		std::cout << '\n';
		for(int x = 0; x < GRID_WIDTH * 2 - 1; x++)
		{
			std::cout << "_";
		}
	}

	std::cout << '\n';
	
	for(int y = 0; y < GRID_HEIGHT; y++)
	{
		for(int x = 0; x < GRID_WIDTH; x++)
		{
			std::cout << grid[y * GRID_WIDTH + x] << ' ';
		}
			
		std::cout << '\n';
	}
	
	std::cout << '\n';
}

void player_turn(char player)
{
	int column_number;
	bool valid;
	
	do
	{
		valid = true;
		std::cout << "Player " << player << ": ";

		std::cin >> column_number;

		if (std::cin.fail())
		{
			std::cout << "That was not a number" << std::endl;
			valid = false;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		
		column_number--;
		
		if((column_number < 0) || (column_number > GRID_WIDTH - 1))
		{
			std::cout << "That column does not exist" << std::endl;
			valid = false;
			continue;
		}

		if(grid[column_number] != '0')
		{
			std::cout << "Column is full." << std::endl;
			valid = false;
		}
	}
	while(!valid);

	for (int y = GRID_HEIGHT - 1; y > -1; y--)
	{
		const int EMPTY_SPACE = y * GRID_WIDTH + column_number;

		if (grid[EMPTY_SPACE] == '0')
		{
			grid[EMPTY_SPACE] = player;
			break;
		}
	}
}

bool four_in_a_row(char player)
{
	// Horizontal check:
	for(int y = 0; y < 6; y++)
		for(int x = 0; x < 4; x++)
			if(grid[y * GRID_WIDTH + x] == player &&
			   	grid[y * GRID_WIDTH + x + 1] == player &&
			   	grid[y * GRID_WIDTH + x + 2] == player &&
			   	grid[y * GRID_WIDTH + x + 3] == player)
				return true;

	// Vertical check:
	for(int y = 0; y < 7; y++)
		for(int x = 0; x < 3; x++)
			if(grid[y * GRID_WIDTH + x] == player &&
				grid[(y+1) * GRID_WIDTH + x] == player &&
				grid[(y+2) * GRID_WIDTH + x] == player &&
				grid[(y+3) * GRID_WIDTH + x] == player)
				return true;

	// Diagonal checks
	for (int y = 0; y < GRID_HEIGHT - 3; y++) {
		for (int x = 0; x < GRID_WIDTH - 3; x++) {
			if (
				(grid[y * GRID_WIDTH + x + 3] == player &&
				grid[(y + 1) * GRID_WIDTH + x + 2] == player &&
				grid[(y + 2) * GRID_WIDTH + x + 1] == player &&
				grid[(y + 3) * GRID_WIDTH + x] == player)
				||
				(grid[y * GRID_WIDTH + x] == player &&
				grid[(y + 1) * GRID_WIDTH + x + 1] == player &&
				grid[(y + 2) * GRID_WIDTH + x + 2] == player &&
				grid[(y + 3) * GRID_WIDTH + x + 3] == player)) {
				return true;
			}
		}
	}

	return false;
}

bool grid_is_full()
{
	// If top row is full, then grid is full
	for (int x = 0; x < GRID_WIDTH; x++)
	{
		if (grid[x] == '0')
		{
			return false;
		}
	}
	return true;
}

void clear_screen()
{
	for(int i = 0; i < 100; i++)
		std::cout << '\n';
}
