#ifndef SHAPES_CONSTANTS_H
#define SHAPES_CONSTANTS_H

#include <string>

const std::string CIRCLE = "circle";
const std::string RECTANGLE = "rectangle";
const std::string TRIANGLE = "triangle";
const std::string LINE = "line";

const std::string RECTANGLE_OUTPUT_FORMAT = "Rectangle\n";
const std::string CIRCLE_OUTPUT_FORMAT = "Circle\n";
const std::string LINE_OUTPUT_FORMAT = "Line\n";
const std::string TRIANGLE_OUTPUT_FORMAT = "Triangle\n";

const std::string LEFT_OUTPUT_FORMAT = "Left top: ";
const std::string WIDTH_OUTPUT_FORMAT = "Width: ";
const std::string HEIGHT_OUTPUT_FORMAT = "Height: ";
const std::string RADIUS_OUTPUT_FORMAT = "Radius: ";
const std::string CENTER_OUTPUT_FORMAT = "Center: ";
const std::string VERTEX1_OUTPUT_FORMAT = "Vertex 1: ";
const std::string VERTEX2_OUTPUT_FORMAT = "Vertex 1: ";
const std::string VERTEX3_OUTPUT_FORMAT = "Vertex 1: ";
const std::string START_POINT_OUTPUT_FORMAT = "Start point: ";
const std::string END_POINT_OUTPUT_FORMAT = "End point: ";
const std::string FILL_COLOR_OUTPUT_FORMAT = "Fill color: #";
const std::string OUTLINE_COLOR_OUTPUT_FORMAT = "Outline color: #";

const std::string INVALID_COLOR_FORMAT = "Invalid color format. Expected RRGGBB (6 hex digits)\n";
const std::string INVALID_SHAPE_DESCRIPTION = "Invalid shape description: ";
const std::string INVALID_POINT = "Invalid point coordinates\n";
const std::string POSITIVE_NUMBER_REQUIRED = "Value must be positive number\n";
const std::string UNKNOWN_COMMAND = "Unknown command '";
const std::string NO_SHAPES_ADDED = "No shapes added\n";
const std::string ERROR = "Error: ";
const std::string NO_SHAPES_ENTERED ="No shapes entered.";
const std::string CIRCLE_INPUT_FORMAT = "Enter circle parameters: <fillColor> <outlineColor> <x> <y> <radius>\n";
const std::string RECTANGLE_INPUT_FORMAT = "Enter: <fillColor> <outlineColor> <x> <y> <width> <height>\n";
const std::string TRIANGLE_INPUT_FORMAT = "Enter: <fillColor> <outlineColor> <x1> <y1> <x2> <y2> <x3> <y3>\n";
const std::string LINE_INPUT_FORMAT = "Enter: <color> <x1> <y1> <x2> <y2>\n";

const std::string INVALID_CIRCLE_INPUT = "Invalid input format. Expected: RRGGBB RRGGBB x y radius\n";
const std::string INVALID_CIRCLE_RADIUS = "Radius must be positive\n";
const std::string COLLINEAR_POINTS = "Error: Points must not be collinear\n";

const std::string MAX_AREA_SHAPE_MESSAGE = "Shape with max area: ";
const std::string MIN_PERIMETER_SHAPE_MESSAGE = "Shape with min perimeter:";

#endif //SHAPES_CONSTANTS_H
