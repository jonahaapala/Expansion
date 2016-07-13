# Expansion
Expand or contract an arbitrary polygon.

After downloading all the files, test out the program by typing the following in the terminal:

make run

This is how the expansion program gets compiled and run. You should see the following result:

{
(-1.000000,-1.000000)
(-1.000000,1.000000)
(1.000000,1.000000)
(1.000000,-1.000000)
}
{
(-4.000000,-4.000000)
(-4.000000,4.000000)
(4.000000,4.000000)
(4.000000,-4.000000)
}

The first group of points are the input, and the second are the output. A 2x2 square centered at
the origin was expanded to have a border of 3 units. These default settings are found in the main
directory's .config file.

In the .config file, you can set three variables:
    WIDTH : How big of a border to you want. Must be bigger than 0.
    IN_OUT: Contract the object or expand it. 'In' or 'out'.
    POINTS: A list of ordered points that define the polygon. Must have at least 3 points and they
            must but formatted: "(x,y)"

And that's it! Once these values are set, save the file and type 'make run' to get results.
