#include "../include/astar.h"

Astar::Astar(int w, int h){
  width = w;
  height = h;

  nodes = new Node[width*height];

  for (int x = 0; x < width; x++)
    for (int y = 0; y < height; y++){
      nodes[y * width + x].x = x; // ...because we give each node its own coordinates
      nodes[y * width + x].y = y;
      // nodes[y * width + x].obstacle = false;
      // nodes[y * width + x].parent = nullptr;
      // nodes[y * width + x].visited = false;
    }

		// Create connections - in this case nodes are on a regular grid
		for (int x = 0; x < width; x++)
			for (int y = 0; y < height; y++){
				if(y>0)
					nodes[y*width + x].neighbours.push_back(&nodes[(y - 1) * width + (x + 0)]);
				if(y<height-1)
					nodes[y*width + x].neighbours.push_back(&nodes[(y + 1) * width + (x + 0)]);
				if (x>0)
					nodes[y*width + x].neighbours.push_back(&nodes[(y + 0) * width + (x - 1)]);
				if(x<width-1)
					nodes[y*width + x].neighbours.push_back(&nodes[(y + 0) * width + (x + 1)]);

				// We can also connect diagonally
				/*if (y>0 && x>0)
					nodes[y*width + x].neighbours.push_back(&nodes[(y - 1) * width + (x - 1)]);
				if (y<height-1 && x>0)
					nodes[y*width + x].neighbours.push_back(&nodes[(y + 1) * width + (x - 1)]);
				if (y>0 && x<width-1)
					nodes[y*width + x].neighbours.push_back(&nodes[(y - 1) * width + (x + 1)]);
				if (y<height - 1 && x<width-1)
					nodes[y*width + x].neighbours.push_back(&nodes[(y + 1) * width + (x + 1)]);
				*/
			}

}

void Astar::setStartnEnd(int x1, int y1, int x2, int y2){
  start = &nodes[y1*width + x1];
  end = &nodes[y2*width + x2];
}

