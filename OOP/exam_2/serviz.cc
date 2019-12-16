#include "serviz.hh"

Serviz::Serviz(vector<Clients> clients, vector<Car> cars, vector<Order> orders) 
	: clients(clients), cars(cars), orders(orders) {};

void Serviz::add_car(Car car){
	if (cars.max_size() <= cars.size()) throw FullServiz();
	else {
		cars.push_back(car);
	}
}
vector<Order> Serviz::get_orders_for_client(Clients client){
	vector<Order> cl_orders;
	for (int i = 0; i < orders.size(); i++){
		if (orders[i].get_cl_email() == client.get_email()
		orders[i].get_cl_name() == client.get_name()) {
			cl_orders.push_back(orders[i]);
		}
	}
	if (cl_orders.size() == 0) throw NoSuchClient();
	return cl_orders;
}
vector<Order> Serviz::get_orders_for_cars(Car car){
	vector<Order> car_orders;
	for (int i = 0; i < cars.size(); i++){
		if (orders[i].car.get_fuelType() == car.get_fuelType()
		&& orders[i].car.get_model() == car.get_model()){
			car_orders.push_back(orders[i]);
		}
	}
	if (car_orders.size() == 0) throw NoSuchCar();
	return car_orders;
}
Order Serviz::get_order_by_number(string number){
	Order num_orders;
	return num_orders;
}

vector<Order> Serviz::get_orders_for_motors(Motor car){
	throw NoMotors();
}
void Serviz::add_motor(Motor motor){
	throw NoMotors();
}
