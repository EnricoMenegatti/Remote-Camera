
MODALITA' DI FUNZIONAMENTO

1.	SCATTO REMOTO (VIA BLUETOOTH DA TELEFONO)
2.	TIMELAPSE (IMPOSTABILE E AVVIABILE VIA BLUETOOTH O DA OLED)
3.	FOTOTRAPPOLA LASER (SU INTERRUZIONE DI RAGGIO LASER)
4. 	FOTOTRAPPOLA ACUSTICA (SU FORTE RUMORE)



0.	CONFIGURAZIONE FILE BLUETOOTH CAMBIO MODALITA'

		8 CARATTERI		--->	X0 			--->	MODALITA'
						--->	0X 			--->	FINE STRINGA

			MODALITA'		--->	R 			---> 	SCATTO REMOTO
							--->	T 			--->	TIMELAPSE
							--->	L 			--->	FOTOTRAPPOLA LASER
							--->	A 			--->	FOTOTRAPPOLA ACUSTICA

			FINE			--->	+			--->	CARATTERE FINALE DELLA STRINGA


1.	CONFIGURAZIONE FILE BLUETOOTH SCATTO REMOTO

		8 CARATTERI 	--->	XX000000  	--->	COMANDO
						--->  	00XXXX00  	--->	VALORE TEMPO
						--->	000000X0	--->	UNITA' TEMPO 
						--->	0000000X	--->	FINE STRINGA
						
			COMANDI			--->	FF-----X	---> 	MESSA A FUOCO STANDARD(1S)
							--->	FFXXXXXX	--->	FUOCO CON TEMPO DIVERSO DA STANDARD
							--->	SS-----X	--->	SCATTO STANDARD(DA IMPOSTAZIONI MACCHINA)
							--->	SSXXXXXX	--->	SCATTO CON MACCHINA IN BULB
							---> 	FS-----X	--->	FUOCO + SCATTO STANDARD(1S + SCATTO MACCHINA)


			UNITA' 			--->	m			--->	MILLISECONDI
							--->	S			--->	SECONDI
							--->	M			--->	MINUTI

			FINE			--->	*			--->	CARATTERE FINALE DELLA STRINGA


3.	CONFIGURAZIONE FILE BLUETOOTH FOTOTRAPPOLA LASER

		8 CARATTERI		--->	XXXXXXX0  	--->	VALORE TEMPO IN ms (MAX 9'999'999 ms)
						--->	0000000X	--->	FINE STRINGA

			FINE			--->	*			--->	CARATTERE FINALE DELLA STRINGA


4.	CONFIGURAZIONE FILE BLUETOOTH FOTOTRAPPOLA ACUSTICA

		8 CARATTERI		--->	XXXXXXX0  	--->	VALORE TEMPO IN ms (MAX 9'999'999 ms)
						--->	0000000X	--->	FINE STRINGA

			FINE			--->	*			--->	CARATTERE FINALE DELLA STRINGA