/* Treino G 2015*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_MAZE 100

#define SLASH 	'/'
#define BSLASH 	'\\'
#define VBAR	'|'

char maze[MAX_MAZE][MAX_MAZE];
int maze_w;
int maze_h;

typedef struct path{
	int x;
	int y;
} mz_path;

mz_path * mzpath_ptr;
mz_path mzpath[MAX_MAZE*MAX_MAZE];

int traverse_maze(mz_path * path_ptr);
int follow_path(int px, int py,mz_path * path_ptr);

int main(void) {
	int bufferi;
	int i;

	do {
		if (scanf("%d",&bufferi) == EOF) break;
		maze_h = bufferi;

		if (scanf("%d",&bufferi) == EOF) break;
		maze_w = bufferi;

		for (i = 0; i < maze_h; ++i) {
			scanf("%s",maze[i]);
		}

		mzpath_ptr = mzpath;
		mz_path * path_ptr = mzpath;

		if (traverse_maze(path_ptr) == 1) {

			mzpath_ptr = mzpath_ptr - sizeof(mz_path);
			while (mzpath_ptr > mzpath) {
				printf("(%d,%d),",mzpath_ptr->y +1,mzpath_ptr->x +1);
				mzpath_ptr = mzpath_ptr - sizeof(mz_path);
			}
			printf("(%d,%d)\n",mzpath_ptr->y +1,mzpath_ptr->x +1);

		} else {
			printf("No Path!\n");
		}

	} while (1);

	return 0;
}

/*
 * |:124 \:92 /:47
 */

int traverse_maze(mz_path * path_ptr) {
	int i;
	for (i = 0; i < maze_w; ++i) {
		if (maze[maze_h-1][i] == VBAR || maze[maze_h-1][i] == BSLASH || maze[maze_h-1][i] == SLASH) {
			/* we got ourself an exit... follow it!*/

			if (follow_path(i,maze_h-1,path_ptr) == 1) return 1;
			mzpath_ptr = mzpath;
		}
	}
	return 0;
}

int follow_path(int px, int py,mz_path * path_ptr) {

	/*	POSSIBLE MOVES
	 *	 \     |     /    \/    /\     /    \	 	\    /	    |    |
 	 *	  |    |    |                 /      \      /    \     /	  \
	 */

	while (1) {
		path_ptr->x = px;
		path_ptr->y = py;
		path_ptr = path_ptr + sizeof(mz_path);
		mzpath_ptr = path_ptr;

		if (py == 0) {
			/* We have reached the top of the maze */
			return 1;
		}
		if (px == 0) {
			/*
			 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
			 * We are in the right border of the maze
			 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
			 */

			if (maze[py][px] == VBAR) { /* We are in a | path */
				if (maze[py-1][px] == VBAR) {
					if (maze[py-1][px+1] == SLASH) {
						/*
						 * We have this path in front of us
						 *   |/
						 *   |
						 */
						if (follow_path(px,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;
						if (follow_path(px+1,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;
						return 0;

					} else {
						/*
						 * We have this path in front of us
						 *   |
						 *   |
						 */
						py = py-1;

					}
				} else if (maze[py-1][px+1] == SLASH) {
					/*
					 * We have this path in front of us
					 *    /
					 *   |
					 */
					px = px+1;
					py = py-1;

				} else {
					/*
					 * We have this path in front of us
					 *  ###
					 *   |
					 */
					mzpath_ptr = path_ptr;
					return 0;

				}

			} else if (maze[py][px] == BSLASH) {  /* We are in a \ path */
				if (maze[py-1][px] == SLASH) {
					/*
					 * We have this path in front of us
					 *   /
					 *   \
					 */
					py = py-1;

				} else {
					/*
					 * We have this path in front of us
					 *   #
					 *   \
					 */
					mzpath_ptr = path_ptr;
					return 0;
				}

			} else if (maze[py][px] == SLASH){ /* We are in a / path*/
				if (maze[py][px+1] == BSLASH) {
					/* We have a sideways path /\ */
					if (maze[py-1][px] == BSLASH) {
						/*
						 * We have this path in front of us
						 *  \
						 *  /\
						 */
						if (follow_path(px,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;

					}
					if (maze[py-1][px+1] == SLASH) {
						/*
						 * We have this path in front of us
						 *  ?/
						 *  /\
						 */
						if (follow_path(px+1,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;

					} else if (maze[py-1][px+1] == VBAR) {
						/*
						 * We have this path in front of us
						 *  ?|
						 *  /\
						 */
						if (follow_path(px+1,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;

					}
					/* follow the /\ path */
					if (px < maze_w-2) {
						if (maze[py][px+2] == SLASH) {
							path_ptr->x = px+1;
							path_ptr->y = py;
							path_ptr = path_ptr + sizeof(mz_path);
							mzpath_ptr = path_ptr;

							if (follow_path(px+2,py,path_ptr) == 1) return 1;

							path_ptr = path_ptr - sizeof(mz_path);
							mzpath_ptr = path_ptr;
							return 0;
						}
					}
					mzpath_ptr = path_ptr;
					return 0;

				} else {
					if (maze[py-1][px] == BSLASH) {
						if (maze[py-1][px+1] == SLASH) {
							/*
							 * We have this path in front of us
							 *  \/
							 *  /
							 */
							if (follow_path(px,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							if (follow_path(px+1,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							return 0;

						} else if (maze[py-1][px+1] == VBAR) {
							/*
							 * We have this path in front of us
							 *  \|
							 *  /
							 */
							if (follow_path(px,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							if (follow_path(px+1,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							return 0;

						} else {
							/*
							 * We have this path in front of us
							 *  \
							 *  /
							 */
							py = py-1;

						}
					} else if (maze[py-1][px+1] == SLASH) {
						/*
						 * We have this path in front of us
						 *   /
						 *  /
						 */
						px = px+1;
						py = py-1;

					} else if (maze[py-1][px+1] == VBAR) {
						/*
						 * We have this path in front of us
						 *   |
						 *  /
						 */
						px = px+1;
						py = py-1;

					} else {
						/*
						 * We have this path in front of us
						 *  #
						 *  /
						 */
						mzpath_ptr = path_ptr;
						return 0;
					}
				}
			}

		} else if (px == maze_w-1) {
			/*
			 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
			 * We are in the left border of the maze
			 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
			 */

			if (maze[py][px] == VBAR) { /* We are in a | path */
				if (maze[py-1][px-1] == BSLASH) {
					if (maze[py-1][px] == VBAR) {
						/*
						 * We have this path in front of us
						 *  \|
						 *   |
						 */
						if (follow_path(px-1,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;
						if (follow_path(px,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;
						return 0;

					} else {
						/*
						 * We have this path in front of us
						 *  \
						 *   |
						 */
						px = px-1;
						py = py-1;
					}
				} else if (maze[py-1][px] == VBAR) {
					/*
					 * We have this path in front of us
					 *   |
					 *   |
					 */
					py = py-1;

				} else {
					/*
					 * We have this path in front of us
					 *  ###
					 *   |
					 */
					mzpath_ptr = path_ptr;
					return 0;

				}

			} else if (maze[py][px] == BSLASH) {  /* We are in a \ path */
				if (maze[py][px-1] == SLASH) {
					/* We have a sideways path /\ */
					if (maze[py-1][px] == SLASH) {
						/*
						 * We have this path in front of us
						 *   /
						 *  /\
						 */
						if (follow_path(px,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;
					}
					if (maze[py-1][px-1] == BSLASH) {
						/*
						 * We have this path in front of us
						 *  \?
						 *  /\
						 */
						if (follow_path(px-1,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;

					} else if (maze[py-1][px-1] == VBAR) {
						/*
						 * We have this path in front of us
						 *  |?
						 *  /\
						 */
						if (follow_path(px-1,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;

					}
					/* follow the /\ path */
					if (px > 1) {
						if (maze[py][px-2] == BSLASH) {
							path_ptr->x = px-1;
							path_ptr->y = py;
							path_ptr = path_ptr + sizeof(mz_path);
							mzpath_ptr = path_ptr;

							if (follow_path(px-2,py,path_ptr) == 1) return 1;

							path_ptr = path_ptr - sizeof(mz_path);
							mzpath_ptr = path_ptr;
							return 0;
						}
					}
					mzpath_ptr = path_ptr;
					return 0;

				} else {
					if (maze[py-1][px] == SLASH) {
						if (maze[py-1][px-1] == BSLASH) {
							/*
							 * We have this path in front of us
							 *  \/
							 *   \
							 */
							if (follow_path(px,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							if (follow_path(px-1,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							return 0;

						} else if (maze[py-1][px-1] == VBAR) {
							/*
							 * We have this path in front of us
							 *  |/
							 *   \
							 */
							if (follow_path(px,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							if (follow_path(px-1,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							return 0;

						} else {
							/*
							 * We have this path in front of us
							 *   /
							 *   \
							 */
							py = py-1;
						}
					} else if (maze[py-1][px-1] == BSLASH) {
						/*
						 * We have this path in front of us
						 *  \
						 *   \
						 */
						px = px-1;
						py = py-1;

					} else if (maze[py-1][px-1] == VBAR) {
						/*
						 * We have this path in front of us
						 *  |
						 *   \
						 */
						px = px-1;
						py = py-1;

					} else {
						/*
						 * We have this path in front of us
						 *   #
						 *   \
						 */
						mzpath_ptr = path_ptr;
						return 0;
					}
				}

			} else if (maze[py][px] == SLASH){ /* We are in a / path*/
				if (maze[py-1][px] == BSLASH) {
					/*
					 * We have this path in front of us
					 *  \
					 *  /
					 */
					py = py-1;

				} else {
					/*
					 * We have this path in front of us
					 *  #
					 *  /
					 */
					mzpath_ptr = path_ptr;
					return 0;
				}
			}
		} else {
			/*
			 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
			 * We are somewhere in the middle of the maze
			 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
			 */

			if (maze[py][px] == VBAR) { /* We are in a | path */
				if (maze[py-1][px-1] == BSLASH) {
					if (maze[py-1][px] == VBAR) {
						if (maze[py-1][px+1] == SLASH) {
							/*
							 * We have this path in front of us
							 *  \|/
							 *   |
							 */
							if (follow_path(px-1,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							if (follow_path(px,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							if (follow_path(px+1,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							return 0;

						} else {
							/*
							 * We have this path in front of us
							 *  \|
							 *   |
							 */
							if (follow_path(px-1,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							if (follow_path(px,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							return 0;

						}
					} else if (maze[py-1][px+1] == SLASH) {
						/*
						 * We have this path in front of us
						 *  \ /
						 *   |
						 */
						if (follow_path(px-1,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;
						if (follow_path(px+1,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;
						return 0;

					} else {
						/*
						 * We have this path in front of us
						 *  \
						 *   |
						 */
						px = px-1;
						py = py-1;
					}
				} else if (maze[py-1][px] == VBAR) {
					if (maze[py-1][px+1] == SLASH) {
						/*
						 * We have this path in front of us
						 *   |/
						 *   |
						 */
						if (follow_path(px,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;
						if (follow_path(px+1,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;
						return 0;

					} else {
						/*
						 * We have this path in front of us
						 *   |
						 *   |
						 */
						py = py-1;

					}
				} else if (maze[py-1][px+1] == SLASH) {
					/*
					 * We have this path in front of us
					 *    /
					 *   |
					 */
					px = px+1;
					py = py-1;

				} else {
					/*
					 * We have this path in front of us
					 *  ###
					 *   |
					 */
					mzpath_ptr = path_ptr;
					return 0;

				}

			} else if (maze[py][px] == BSLASH) {  /* We are in a \ path */
				if (maze[py][px-1] == SLASH) {
					/* We have a sideways path /\ */
					if (maze[py-1][px] == SLASH) {
						/*
						 * We have this path in front of us
						 *   /
						 *  /\
						 */
						if (follow_path(px,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;
					}
					if (maze[py-1][px-1] == BSLASH) {
						/*
						 * We have this path in front of us
						 *  \?
						 *  /\
						 */
						if (follow_path(px-1,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;

					} else if (maze[py-1][px-1] == VBAR) {
						/*
						 * We have this path in front of us
						 *  |?
						 *  /\
						 */
						if (follow_path(px-1,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;

					}
					/* follow the /\ path */
					if (px > 1) {
						if (maze[py][px-2] == BSLASH) {
							path_ptr->x = px-1;
							path_ptr->y = py;
							path_ptr = path_ptr + sizeof(mz_path);
							mzpath_ptr = path_ptr;

							if (follow_path(px-2,py,path_ptr) == 1) return 1;

							path_ptr = path_ptr - sizeof(mz_path);
							mzpath_ptr = path_ptr;
							return 0;
						}
					}
					mzpath_ptr = path_ptr;
					return 0;

				} else {
					if (maze[py-1][px] == SLASH) {
						if (maze[py-1][px-1] == BSLASH) {
							/*
							 * We have this path in front of us
							 *  \/
							 *   \
							 */
							if (follow_path(px,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							if (follow_path(px-1,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							return 0;

						} else if (maze[py-1][px-1] == VBAR) {
							/*
							 * We have this path in front of us
							 *  |/
							 *   \
							 */
							if (follow_path(px,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							if (follow_path(px-1,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							return 0;

						} else {
							/*
							 * We have this path in front of us
							 *   /
							 *   \
							 */
							py = py-1;
						}
					} else if (maze[py-1][px-1] == BSLASH) {
						/*
						 * We have this path in front of us
						 *  \
						 *   \
						 */
						px = px-1;
						py = py-1;

					} else if (maze[py-1][px-1] == VBAR) {
						/*
						 * We have this path in front of us
						 *  |
						 *   \
						 */
						px = px-1;
						py = py-1;

					} else {
						/*
						 * We have this path in front of us
						 *   #
						 *   \
						 */
						mzpath_ptr = path_ptr;
						return 0;
					}
				}

			} else if (maze[py][px] == SLASH){ /* We are in a / path*/
				if (maze[py][px+1] == BSLASH) {
					/* We have a sideways path /\ */
					if (maze[py-1][px] == BSLASH) {
						/*
						 * We have this path in front of us
						 *  \
						 *  /\
						 */
						if (follow_path(px,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;

					}
					if (maze[py-1][px+1] == SLASH) {
						/*
						 * We have this path in front of us
						 *  ?/
						 *  /\
						 */
						if (follow_path(px+1,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;

					} else if (maze[py-1][px+1] == VBAR) {
						/*
						 * We have this path in front of us
						 *  ?|
						 *  /\
						 */
						if (follow_path(px+1,py-1,path_ptr) == 1) return 1;
						mzpath_ptr = path_ptr;

					}
					/* follow the /\ path */
					if (px < maze_w-2) {
						if (maze[py][px+2] == SLASH) {
							path_ptr->x = px+1;
							path_ptr->y = py;
							path_ptr = path_ptr + sizeof(mz_path);
							mzpath_ptr = path_ptr;

							if (follow_path(px+2,py,path_ptr) == 1) return 1;

							path_ptr = path_ptr - sizeof(mz_path);
							mzpath_ptr = path_ptr;
							return 0;
						}
					}
					return 0;

				} else {
					if (maze[py-1][px] == BSLASH) {
						if (maze[py-1][px+1] == SLASH) {
							/*
							 * We have this path in front of us
							 *  \/
							 *  /
							 */
							if (follow_path(px,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							if (follow_path(px+1,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							return 0;

						} else if (maze[py-1][px+1] == VBAR) {
							/*
							 * We have this path in front of us
							 *  \|
							 *  /
							 */
							if (follow_path(px,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							if (follow_path(px+1,py-1,path_ptr) == 1) return 1;
							mzpath_ptr = path_ptr;
							return 0;

						} else {
							/*
							 * We have this path in front of us
							 *  \
							 *  /
							 */
							py = py-1;

						}
					} else if (maze[py-1][px+1] == SLASH) {
						/*
						 * We have this path in front of us
						 *   /
						 *  /
						 */
						px = px+1;
						py = py-1;

					} else if (maze[py-1][px+1] == VBAR) {
						/*
						 * We have this path in front of us
						 *   |
						 *  /
						 */
						px = px+1;
						py = py-1;

					} else {
						/*
						 * We have this path in front of us
						 *  #
						 *  /
						 */
						mzpath_ptr = path_ptr;
						return 0;
					}
				}
			}
		}

	}
	mzpath_ptr = path_ptr;
	return 0;
}


