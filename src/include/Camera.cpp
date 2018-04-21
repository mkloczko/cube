#include "Camera.hpp"

#include <Eigen/Geometry>
#include <Eigen/Dense>

Eigen::Matrix4f projectionMatrix(float l, float r, float b, float t, float n, float f){
    Eigen::Matrix4f pmat;

    pmat << (2*n)/(r-l), 0          ,  (r+l)/(r-l),   0,
            0          , (2*n)/(t-b),  (t+b)/(t-b),   0,
            0          , 0          ,  -(f+n)/(f-n), (-2*f*n)/(f-n),
            0          ,           0,  -1,  0;

    return pmat;
}

Eigen::Matrix4f lookAtMatrix(Eigen::Vector3f eye, Eigen::Vector3f look, Eigen::Vector3f up)
{
    Eigen::Vector3f f, s, u;
    Eigen::Matrix4f m, t;

    f = (look - eye).normalized();
    s = f.cross(up.normalized());
    u = s.cross(f);



    m <<  s.x(),  s.y(),  s.z(), 0,
            u.x(),  u.y(),  u.z(), 0,
            -f.x(), -f.y(), -f.z(), 0,
            0,      0,      0, 1;

    t << 1, 0, 0, -eye.x(),
            0, 1, 0, -eye.y(),
            0, 0, 1, -eye.z(),
            0, 0, 0,        1;

    Eigen::Matrix4f ret = m*t;

    return ret;
}

Eigen::Matrix4f orthoMatrix(float l, float r, float b, float t, float n, float f){

    Eigen::Matrix4f pmat;

    pmat << 2/(r-l), 0      , 0      , (r+l)/(l-r),
            0      , 2/(t-b), 0      , (t+b)/(b-t),
            0      ,       0, 2/(n-f), (f+n)/(f-n),
            0      ,       0,       0,           1;

    pmat << 2/(r-l)    ,     0      ,     0      , 0,
            0          ,     2/(t-b),     0      , 0,
            0          ,           0,     2/(n-f), 0,
            (r+l)/(l-r), (t+b)/(b-t), (f+n)/(n-f), 1;

    return pmat;
}
