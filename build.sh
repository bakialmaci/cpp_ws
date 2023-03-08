WS_FOLDER=$1
RUN=$2

if  [ -d "$WS_FOLDER" ]; then
    echo "$1, is building..."

    BUILD_FOLDER=$WS_FOLDER/build

    if [ -d "$BUILD_FOLDER" ]; then
        echo "$BUILD_FOLDER exists. Will not be created."
    else
        echo "$BUILD_FOLDER does not exist. Created."
        mkdir -p $BUILD_FOLDER
    fi

    echo "Enetering $BUILD_FOLDER ..."
    cd $BUILD_FOLDER

    echo "Running cmake ..."
    cmake ..
    make all

    echo "Build finished. Executable is in $BUILD_FOLDER/bin."

    if [ "$RUN" == "run" ]; then
        echo "Running ..."
        ./bin/$WS_FOLDER
    else
        echo "Build finished, but will not run."
    fi

else
    echo "$WS_FOLDER not exists! Please check your input."
    exit 0
fi