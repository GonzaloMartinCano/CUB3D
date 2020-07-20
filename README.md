# CUB3D_FT
Este proyecto está inspirado en el juego mundialmente conocido, considerado como el primer FPS jamás realizado. Le permitirá explorar la técnica del ray-casting. El objetivo será crear una vista dinámica dentro de un mapa, en el que poder observar diferentes texturas para muros, objetos, etc.

![Alt text](https://raw.githubusercontent.com/Zalillo18/CUB3D/master/Pantalla_inicio.png)

Para compilar:

    make re
  
Para ejecutar, necesitamos pasar un archivo de configuración .cub válido con los datos del mapa (resolución, texturas, mapa, etc)(tenemos dos ejemplos para cargar, tx.cub y tx2.cub):

    ./Cub3D tx.cub
 
*Podemos crear un nuevo archivo de configuración o cambiar el existente para crear un nuevo mapa, pero debemos respetar las reglas de configuración (en el subject podemos encontrar los requisitos, o podemos probar y el propio programa nos dirá el error y que debemos módificar). 
*Tanto minilibx como el resto de librerias referenciadas ya están preparadas para usarse

Referencias:

      https://lodev.org/cgtutor/raycasting.html
      https://qst0.github.io/ft_libgfx/man_mlx_loop.html
      https://harm-smits.github.io/42docs/libs/minilibx
      https://asidesigned.com/project-wolf3d.html
