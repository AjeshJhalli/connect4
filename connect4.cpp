#include <iostream>

char grid[6][7];
	
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
		
		if(player == '1')
			player = '2';
		else if(player == '2')
			player = '1';

		clear_screen();
	}
	
	std::cin.get();
	std::cin.get();
	
	return 0;
}

void setup_grid()
{
	for(int i = 0; i < 6; i++)
		for(int j = 0; j < 7; j++)
			grid[i][j] = '0';
}

void display_grid()
{
	std::cout << std::endl;
	std::cout << "Enter a column number (1-7) to put a piece into that column." << std::endl;
	std::cout << std::endl;
	
	for(int i = 0; i < 6; i++)
	{
		for(int j = 0; j < 7; j++)
			std::cout << grid[i][j] << ' ';
	
		std::cout << std::endl;
	}
	
	std::cout << std::endl;
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
		
		column_number--;
		
		if((column_number < 0) || (column_number > 6))
		{
			std::cout << "That number was not between 1 and 7" << std::endl;
			valid = false;
			continue;
		}

		if(grid[0][column_number] != '0')
		{
			std::cout << "Column is full." << std::endl;
			valid = false;
		}
	}
	while(!valid);
	
	for(int i = 0; i < 6; i++)
	{
		if(grid[i + 1][column_number] != '0')
		{
			grid[i][column_number] = player;
			break;
		}
		else if(i == 6)
		{
			grid[i][column_number] = player;
			break;
		}
	}
}

bool four_in_a_row(char player)
{
	// Horizontal check:
	
	for(int i = 0; i < 6; i++)
		
		for(int j = 0; j < 4; j++)
			
			if(grid[i][j] == player && grid[i][j+1] == player)
				if(grid[i][j+2] == player && grid[i][j+3] == player)
					return true;

	// Vertical check:
	
	for(int i = 0; i < 3; i++)
		
		for(int j = 0; j < 7; j++)
			
			if(grid[i][j] == player && grid[i+1][j] == player)
				if(grid[i+2][j] == player && grid[i+3][j] == player)
					return true;
				
	// Diagonal check:
	
	for(int y = 0; y < 3; y++)
	{
		for(int x = 0; x < 7; x++)
		{
			if(grid[y][x] == player)
			{
								// Diagonally left:
				if(grid[y+1][x-1] == player)
				{
					if(grid[y+2][x-2] == player)
						if(grid[y+3][x-3] == player)
							return true;
				}
				
				if(grid[y+1][x+1] == player)
				{
					if(grid[y+2][x+2] == player)
						if(grid[y+3][x+3] == player)
							return true;
				}
			}
		}
	}

	return false;
}

bool grid_is_full()
{
	for(int y = 0; y < 6; y++)
	{
		for(int x = 0; x < 7; x++)
		{
			if(grid[y][x] == '0')
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