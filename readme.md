
# REMOTE CAMERA CONTROL

## MODALITA' DI FUNZIONAMENTO

###	CONFIGURAZIONE FILE BLUETOOTH CAMBIO MODALITA'

|			OPERAZIONE | BIT 1 | BIT 0 |  
| -------------------- | ----- | ----- |  
|				  HOME |  	 H |	 + |  
|		 SCATTO REMOTO |	 R |	 + |  
|			 TIMELAPSE |	 T |	 + | 
|	FOTOTRAPPOLA LASER |	 L |	 + |
|FOTOTRAPPOLA ACUSTICA |	 A |	 + |


###	CONFIGURAZIONE FILE BLUETOOTH SCATTO REMOTO

|						OPERAZIONE | BIT 7 | BIT 6 | BIT 5 | BIT 4 | BIT 3 | BIT 2 | BIT 1 | BIT 0 |  
| -------------------------------- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- |  
|				FUOCO STANDARD(1S) |	 F |	 F |	 - |	 - |	 - |	 - |	 - |	 * |  
|				   FUOCO IMPOSTATO |	 F |	 F |   TIME|   TIME|   TIME|   TIME| UNITA'|	 * |  
|  SCATTO STANDARD(TEMPO MACCHINA) |	 S |	 S |	 - |	 - |	 - |	 - |	 - |	 * | 
|  SCATTO IMPOSTATO(MACCHINA BULB) |	 F |	 S |   TIME|   TIME|   TIME|   TIME| UNITA'|	 * |
|		   FUOCO + SCATTO STANDARD |	 F |	 S |	 - |	 - |	 - |	 - |	 - |	 * |

#### UNITA'
1. MINUTI		--->	M
2. SECONDI		--->	S
3. MILLISECONDI	--->	m


###	CONFIGURAZIONE FILE BLUETOOTH FOTOTRAPPOLA LASER

		8 CARATTERI		--->	XXXXXXX0  	--->	VALORE TEMPO IN ms (MAX 9'999'999 ms)
						--->	0000000X	--->	FINE STRINGA

			FINE			--->	*			--->	CARATTERE FINALE DELLA STRINGA


###	CONFIGURAZIONE FILE BLUETOOTH FOTOTRAPPOLA ACUSTICA

		8 CARATTERI		--->	XXXXXXX0  	--->	VALORE TEMPO IN ms (MAX 9'999'999 ms)
						--->	0000000X	--->	FINE STRINGA

			FINE			--->	*			--->	CARATTERE FINALE DELLA STRINGA