TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        activation.cpp \
        convolutionallayer.cpp \
        denselayer.cpp \
        inputlayer.cpp \
        layer.cpp \
        main.cpp \
        matrix.cpp \
        neuralnetwork.cpp \
        outputlayer.cpp \
        tensor.cpp \
        util.cpp

HEADERS += \
    activation.h \
    convolutionallayer.h \
    denselayer.h \
    inputlayer.h \
    layer.h \
    matrix.h \
    neuralnetwork.h \
    outputlayer.h \
    tensor.h \
    util.h
