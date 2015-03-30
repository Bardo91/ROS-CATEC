
Este módulo sirve para monitorizar el estado de UGVs, como el caso de los tira-lineas, en el Testbed.


¡¡ATENCIÓN!!


Este paquete NO tiene aún implementado un modelo para su simulación en Gazebo. Queda por hacer.

Debe de ejecutarse el nodo de comunicación con el tesbed del paquete uav: rosrun uav qnx_hb_state_receiver
Esto es debido a que, de cara a QNX, el tira-lineas es como un Hummingbird más. Por lo que se debe configurar en QNX como tal dentro de PandH_control_UAL (archivo ar_config).

En el tesbed, los objetos están nombrados como siguen:

* Siguelineas 1 --> O12
* Siguelineas 2 --> O13
* Siguelineas 3 --> O14

NOTA: como no se comandan, sólo hay que descomentar los procesos de lectura de estado de Vicon en run_bc
