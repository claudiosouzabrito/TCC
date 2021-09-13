#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/cloud/ROS/TCC/src/turtlebot3_teleop"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/cloud/ROS/TCC/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/cloud/ROS/TCC/install/lib/python3/dist-packages:/home/cloud/ROS/TCC/build/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/cloud/ROS/TCC/build" \
    "/usr/bin/python3" \
    "/home/cloud/ROS/TCC/src/turtlebot3_teleop/setup.py" \
     \
    build --build-base "/home/cloud/ROS/TCC/build/turtlebot3_teleop" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/cloud/ROS/TCC/install" --install-scripts="/home/cloud/ROS/TCC/install/bin"
