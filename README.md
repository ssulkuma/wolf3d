# wolf3d
Third graphics/game development branch project of Hive Helsinki. </br>
The goal of this project was to write, using the ray casting technique, a 3D representation of a maze in which a player can find their way.</br>
The project is based on the famous game Wolfenstein3D.

The project uses the 42 Network MinilibX (https://github.com/42Paris/minilibx-linux).

To compile the program and run it
```
make home ; ./wolf3d [path to map]
```
Example of valid map
```
1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0
0,0,0,0,2,0,0,0,3,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,1
1,1,1,0,0,0,4,0,0,0,0,0,1,0,1,0,0,0,0,3,0,0,0,2,0,0,0,0
0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1
1,3,3,0,0,0,0,0,0,2,0,0,1,0,1,4,0,0,0,0,0,1,0,0,0,0,0,0
0,0,0,0,0,0,4,0,0,0,0,0,1,0,1,0,0,0,2,0,0,0,0,0,0,0,0,1
1,0,4,2,0,0,0,4,0,0,0,0,1,0,1,0,0,0,0,2,0,0,0,4,0,0,0,0
0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1
1,0,0,0,0,3,3,0,0,0,2,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0
0,0,4,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,4,4,4,0,0,2,0,0,1
1,1,1,1,1,3,0,0,0,0,0,0,1,0,1,2,0,0,0,0,0,0,4,0,0,0,0,0
0,0,1,0,0,0,0,0,0,4,3,2,1,0,1,0,0,3,3,0,0,0,0,4,0,0,0,1
1,0,2,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,2,0,0,4,0,0,0
0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1
1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0
```
0 — Empty </br>
1 — Wall </br>
2 — Candelabra </br>
3 — Pumpkin </br>
4 — Tombstone 

Gameplay </br>
Move — up and down arrowkeys / W and S keys</br>
Turn — left and right arrowkeys / A and D keys</br>
Cast a spell — left mouse click

<img width="793" alt="Screenshot 2023-02-09 at 16 34 52" src="https://user-images.githubusercontent.com/95386916/217900926-66152f2c-c68d-41f5-ae50-7661d4085355.png">
<img width="795" alt="Screenshot 2023-02-09 at 16 36 15" src="https://user-images.githubusercontent.com/95386916/217900969-3a3c3127-85a6-4268-8b62-0bb09f482b6a.png">
