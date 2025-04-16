#include <stdio.h>
#include <stdlib.h>
#include "pathfinding.h"

/**
 * create_point - Creates a new point
 * @x: x-coordinate
 * @y: y-coordinate
 * Return: Pointer to the new point
 */
static point_t *create_point(int x, int y)
{
    point_t *point = malloc(sizeof(point_t));

    if (!point)
        return (NULL);
    
    point->x = x;
    point->y = y;
    return (point);
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
static int is_valid_move(char **map, int rows, int cols, int x, int y, int **visited)
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
 * @x: Current x-coordinate
 * @y: Current y-coordinate
 * @target: Target point
 * @visited: 2D array to track visited cells
 * @path: Queue to store the path
 * Return: 1 if path found, 0 otherwise
 */
static int backtrack(char **map, int rows, int cols, int x, int y,
                    point_t const *target, int **visited, queue_t *path)
{
    point_t *point;
    
    /* Print current coordinates being checked */
    printf("Checking coordinates [%d, %d]\n", x, y);
    
    /* Mark current cell as visited */
    visited[y][x] = 1;
    
    /* If target is reached, add current point to path and return success */
    if (x == target->x && y == target->y)
    {
        point = create_point(x, y);
        if (!point)
            return (0);
        
        if (queue_push_front(path, point) == NULL)
        {
            free(point);
            return (0);
        }
        return (1);
    }
    
    /* Try moving RIGHT */
    if (is_valid_move(map, rows, cols, x + 1, y, visited))
    {
        if (backtrack(map, rows, cols, x + 1, y, target, visited, path))
        {
            point = create_point(x, y);
            if (!point)
                return (0);
            
            if (queue_push_front(path, point) == NULL)
            {
                free(point);
                return (0);
            }
            return (1);
        }
    }
    
    /* Try moving BOTTOM */
    if (is_valid_move(map, rows, cols, x, y + 1, visited))
    {
        if (backtrack(map, rows, cols, x, y + 1, target, visited, path))
        {
            point = create_point(x, y);
            if (!point)
                return (0);
            
            if (queue_push_front(path, point) == NULL)
            {
                free(point);
                return (0);
            }
            return (1);
        }
    }
    
    /* Try moving LEFT */
    if (is_valid_move(map, rows, cols, x - 1, y, visited))
    {
        if (backtrack(map, rows, cols, x - 1, y, target, visited, path))
        {
            point = create_point(x, y);
            if (!point)
                return (0);
            
            if (queue_push_front(path, point) == NULL)
            {
                free(point);
                return (0);
            }
            return (1);
        }
    }
    
    /* Try moving TOP */
    if (is_valid_move(map, rows, cols, x, y - 1, visited))
    {
        if (backtrack(map, rows, cols, x, y - 1, target, visited, path))
        {
            point = create_point(x, y);
            if (!point)
                return (0);
            
            if (queue_push_front(path, point) == NULL)
            {
                free(point);
                return (0);
            }
            return (1);
        }
    }
    
    /* No path found from this cell */
    return (0);
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
    
    /* Check for invalid inputs */
    if (!map || !start || !target || rows <= 0 || cols <= 0)
        return (NULL);
    
    /* Create a queue to store the path */
    path = queue_create();
    if (!path)
        return (NULL);
    
    /* Create a 2D array to track visited cells */
    visited = malloc(rows * sizeof(int *));
    if (!visited)
    {
        queue_delete(path);
        return (NULL);
    }
    
    for (i = 0; i < rows; i++)
    {
        visited[i] = calloc(cols, sizeof(int));
        if (!visited[i])
        {
            while (--i >= 0)
                free(visited[i]);
            free(visited);
            queue_delete(path);
            return (NULL);
        }
    }
    
    /* Start backtracking from the start point */
    success = backtrack(map, rows, cols, start->x, start->y, target, visited, path);
    
    /* Free the visited array */
    for (i = 0; i < rows; i++)
        free(visited[i]);
    free(visited);
    
    /* If no path found, delete the queue and return NULL */
    if (!success)
    {
        queue_delete(path);
        return (NULL);
    }
    
    return (path);
}

