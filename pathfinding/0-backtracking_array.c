#include <stdio.h>
#include <stdlib.h>
#include "pathfinding.h"

/**
 * create_point - Creates a new point and adds it to the path
 * @x: x-coordinate
 * @y: y-coordinate
 * @path: Queue to store the path
 * Return: 1 on success, 0 on failure
 */
static int create_point(int x, int y, queue_t *path)
{
	point_t *point = malloc(sizeof(point_t));

	if (!point)
		return (0);

	point->x = x;
	point->y = y;

	if (queue_push_front(path, point) == NULL)
	{
		free(point);
		return (0);
	}
	return (1);
}

/**
 * is_valid_move - Checks if a move is valid
 * @map: 2D array representing the maze
 * @rows: Number of rows in the maze
 * @cols: Number of columns in the maze
 * @x: x-coordinate to check
 * @y: y-coordinate to check
 * @visited: 2D array to track visited cells
 * Return: 1 if valid, 0 otherwise
 */
static int is_valid_move(char **map, int rows, int cols,
		int x, int y, int **visited)
{
	/* Check if coordinates are within bounds */
	if (x < 0 || x >= cols || y < 0 || y >= rows)
		return (0);

	/* Check if cell is walkable and not visited */
	if (map[y][x] == '1' || visited[y][x])
		return (0);

	return (1);
}

/**
 * backtrack - Recursive backtracking function to find path
 * @map: 2D array representing the maze
 * @rows: Number of rows in the maze
 * @cols: Number of columns in the maze
 * @params: Array containing [x, y, target_x, target_y]
 * @visited: 2D array to track visited cells
 * @path: Queue to store the path
 * Return: 1 if path found, 0 otherwise
 */
static int backtrack(char **map, int rows, int cols, int params[4],
		int **visited, queue_t *path)
{
	int x = params[0], y = params[1];
	int target_x = params[2], target_y = params[3];
	int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	int i, new_x, new_y, new_params[4];

	/* Print current coordinates being checked */
	printf("Checking coordinates [%d, %d]\n", x, y);

	/* Mark current cell as visited */
	visited[y][x] = 1;

	/* If target is reached, add current point to path and return success */
	if (x == target_x && y == target_y)
		return (create_point(x, y, path));

	/* Try all four directions: RIGHT, BOTTOM, LEFT, TOP */
	for (i = 0; i < 4; i++)
	{
		new_x = x + directions[i][0];
		new_y = y + directions[i][1];

		if (is_valid_move(map, rows, cols, new_x, new_y, visited))
		{
			new_params[0] = new_x;
			new_params[1] = new_y;
			new_params[2] = target_x;
			new_params[3] = target_y;

			if (backtrack(map, rows, cols, new_params, visited, path))
				return (create_point(x, y, path));
		}
	}

	/* No path found from this cell */
	return (0);
}

/**
 * init_visited - Initializes the visited array
 * @rows: Number of rows
 * @cols: Number of columns
 * Return: 2D array or NULL on failure
 */
static int **init_visited(int rows, int cols)
{
	int **visited;
	int i;

	visited = malloc(rows * sizeof(int *));
	if (!visited)
		return (NULL);

	for (i = 0; i < rows; i++)
	{
		visited[i] = calloc(cols, sizeof(int));
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
	}
	return (visited);
}

/**
 * backtracking_array - Searches for a path from start to target in a 2D array
 * @map: 2D array representing the maze
 * @rows: Number of rows in the maze
 * @cols: Number of columns in the maze
 * @start: Starting point
 * @target: Target point
 * Return: Queue containing the path, or NULL on failure
 */
queue_t *backtracking_array(char **map, int rows, int cols,
		point_t const *start, point_t const *target)
{
	queue_t *path;
	int **visited;
	int i, success = 0;
	int params[4];

	/* Check for invalid inputs */
	if (!map || !start || !target || rows <= 0 || cols <= 0)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);

	visited = init_visited(rows, cols);
	if (!visited)
	{
		queue_delete(path);
		return (NULL);
	}

	params[0] = start->x;
	params[1] = start->y;
	params[2] = target->x;
	params[3] = target->y;
	success = backtrack(map, rows, cols, params, visited, path);

	/* Free the visited array */
	for (i = 0; i < rows; i++)
		free(visited[i]);
	free(visited);

	if (!success)
	{
		queue_delete(path);
		return (NULL);
	}

	return (path);
}
