#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#ifndef INCLUDE_DRAWER_HPP_

#define INCLUDE_DRAWER_HPP_

class drawer {
	unsigned int x_size = 800;
	unsigned int y_size = 600;
    unsigned int marker_size = 3;

    unsigned int new_center_x = x_size / 2;
    unsigned int new_center_y = y_size / 2;

    double limit_x0 = 0;
    double limit_x1 = 0;
    double limit_y0 = 0;
    double limit_y1 = 0;

	double step_x_lin = 0;
	double step_y_lin = 0;
    std::array<double, 4> step_x_log;
    std::array<double, 4> step_y_log;

    double count_marker_y = 0;
    double count_marker_x = 0;

    double scaling_factor_x = 0;
    double scaling_factor_y = 0;

    std::vector<double> x_vec;
    std::vector<double> y_vec;
    std::vector<std::pair<double, double>> coordinates;

    bool test = false;
    bool linear = false;
    bool log = false;

    sf::RenderWindow window;
public:
    void cicle(const std::vector<double>& x_vec_, const std::vector<double>& y_vec_);
    void set_limits_lin();
    void set_limits_log();
    void draw_plate(sf::RenderWindow& window);
    void draw_curve(sf::RenderWindow& window);
    void calculate_scaling_lin();
    void calculate_scaling_log(const double& max, const double& min);
    double calculate_point_x_lin(const std::vector<std::pair<double, double>>& coordinates, const int& i);
    double calculate_point_y_lin(const std::vector<std::pair<double, double>>& coordinates, const int& i);
    double calculate_point_x_log(const std::vector<std::pair<double, double>>& coordinates, const int& i);
    double calculate_point_y_log(const std::vector<std::pair<double, double>>& coordinates, const int& i);
    void set_step_lin();
    void set_step_log();
    void set_count_marker_linear();
    void set_count_marker_log();
    void set_linear();
    void set_log();
    void set_test();
    void close_graph();
    double get_limit_x0();
};

#endif // INCLUDE_DRAWER_HPP_