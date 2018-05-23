# colorgraphs

One of the lectures I was priveleged to attend in the CS 197 Honors Seminar was a deleve into the applicaiton of zero-knowledge proofs in the real world.
I found the subject very interesting and wrote up a little script to make the coloring of graphs easily enough but it's re[resentation was still abstract.
About a week later, the CS 240 students like myself at the time were introducted to QT for their final project.
Although I had no instruction on how to do graphs in QT, I knew I wanted to create a visual representation of the algorithm.

## ./graph

To authenticate using a tripartite graph, Prover sends Verifier a graph G that may be colored by coloring C1.
Given that Verifier has G, they may see the edges tah connect the graph.

Prover may then change the specific colors in the graph, but not the relationships between the colors.
For example, Prover could repaces all the green nodes with red and all the red nodes with green, and the coloring would still be the same.

Verifier may request for the color of two nodes in this recoloring.
If they are the same, the Prover fails.

If G is large and many tests are preformed the chance of being able to fool verifier is arbitrarily low.

## ./graphViewPort

This is just to look at and store graphs.
I couldn't really show the connections between nodes in ./graph at all times becuase they wouldn't be helpful.
./graphViewPort is a tool for visualizing smaller graphs.
