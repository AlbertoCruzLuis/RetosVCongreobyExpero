//Nombre: Alberto
//Apellidos: Cruz Luis
//Correo: alu0101217734@ull.edu.es

double distanciaBonita(std::vector<double> salida, std::vector<double> llegada) {
    
    //Calculate nearest axis to go through
    double axis_x = (salida[0] + llegada[0]) / 2;
    double axis_y = (salida[1] + llegada[1]) / 2;
    
    //Calculate minimum distance from each axis to a street
    return (abs(round(axis_x) - salida[0])) + (abs(round(axis_x) - llegada[0])) 
            + (abs(round(axis_y) - salida[1])) + (abs(round(axis_y) - llegada[1]));
    
}

