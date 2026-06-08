
module emcpp.vector;

import <string>;

template class emcpp::Vector<int, 10, emcpp::SafePolicy>;
template class emcpp::Vector<double, 10, emcpp::SafePolicy>;
template class emcpp::Vector<std::string, 3, emcpp::SafePolicy>;