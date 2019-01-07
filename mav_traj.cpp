#include <mav_trajectory_generation/polynomial_optimization_linear.h>

mav_trajectory_generation::Vertex::Vector vertices;
const int dimension =3;
const int derivative_to_optimize = mav_trajectory_generation::derivative_order::SNAP;
mav_trajectory_generation::Vertex start(dimension), middle(dimension), end(dimension);

//constraint to vertex
start.makeStartOrEnd(Eigen::Vector3d(0,0,1),derivative_to_optimize);
vertices.push_back(start);

middle.addConstraint(mav_trajectory_generation::derivative_order::POSITION, Eigen::Vector3d(1,2,3));
vertices.push_back(middle);

end.makeStartOrEnd(Eigen::Vector3d(2,1,5),derivative_to_optimize);
vertices.push_back(end);

const int N = 10;
mav_trajectory_generation::PolynomialOptimization<N> opt(dimension);
opt.setupFromVertices(vertices,segment_times,derivative_to_optimize);
opt.solveLinear();

mav_trajectory_generation::Segment::Vector segments;
opt.getSegments(&segments);

#include <mav_trajectory_generation/trajectory.h>

mav_trajectory_generation::Trajectory trajectory;
opt.getTrajectory(&trajectory);

//compositing:
mav_trajectory_generation::Trajectory trajectory_with_yaw;
trajectory.getTrajectoryWithAppendedDimension(yaw_trajectory, &trajectory_with_yaw);




subscribe path_segments mav_planning_msgs::PolynomialTrajectory4D 