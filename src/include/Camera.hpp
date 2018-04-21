#ifndef CAMERA_GUARD
#define CAMERA_GUARD

#include <Eigen/Core>

Eigen::Matrix4f projectionMatrix( float left, float right, float bottom, float top, float near, float far);
Eigen::Matrix4f lookAtMatrix(Eigen::Vector3f eye, Eigen::Vector3f look, Eigen::Vector3f up);
Eigen::Matrix4f orthoMatrix(float l, float r, float b, float t, float n, float f);


#endif