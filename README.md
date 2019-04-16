# This is documantation for test task.
## Mathematical approache

There is a cylinder with spherical caps.
It perfectly imitates the linear motion of a sphere.
To understand what the cylinder is cutting out - you need to check each cap individually, which means you just need to check the occurrence of the test point in each of the spheres.
To understand that a point inside a sphere or outside of it is enough to know the length of the vector from its center to the test point and compare this length with the radius of the sphere.
In the case of a cylinder (no caps, we have already dealt with them) you can first find out whether the point lies in the plane perpendicular to the cylinder axis and if it is inside such a plane - check the length of perpendicular from the test point to the cylinder axis.

## Problematics of discrete step

The main problem in discrete step is approximation of intermediate state between steps.
Ideal case is just use infinite amount of steps and get perfect skin.
But we are limited with machines resources and we can use only small number of sphere positions.
And there are 2 approaches for solving problem with discrete step:

1.Assume that step infinitely small (or just small enough to satisfy precision) and approximate sphere moment with linear motion;

2.Use torus and cylinder because all movement could be described as linear and circular movement.

At first glance second approach better, because we can get really good approximation of movement.
But there are a lot of additional problems in comparison to first approach.
For example, determining point in specific sector of a torus is very hard computationally, finding rotation angle or other cases.

So, first approach good enough for this particular task.
I'ts not enough to use only spheres or only cylinders with plain caps because of we will get a lot of points, that shouldn't be there.
Linear motion of a sphere could be represent as set of linked cylinders with spherical caps.
And determining if point inside a sphere or cylinder pretty easy task.

There some illustrations:
![](cyli_without_cap_front.png)
![](cyli_without_cap.png)
![](cyli_without_cap_close.png)
![](only_spheres_front.png)
![](only_spheres.png)