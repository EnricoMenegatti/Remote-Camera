
MODALITA' DI FUNZIONAMENTO

1.	SCATTO REMOTO (VIA BLUETOOTH DA TELEFONO)
2.	TIMELAPSE (IMPOSTABILE E AVVIABILE VIA BLUETOOTH O DA OLED)
3.	FOTOTRAPPOLA LASER (SU INTERRUZIONE DI RAGGIO LASER)
4. 	FOTOTRAPPOLA ACUSTICA (SU FORTE RUMORE)



0.	CONFIGURAZIONE FILE BLUETOOTH CAMBIO MODALITA'

		8 CARATTERI		--->	X0000000	--->	MODALITA'
						--->	0000000X	--->	FINE STRINGA

			MODALITA'		--->	S 			---> 	SCATTO REMOTO
							--->	T 			--->	TIMELAPSE
							--->	L 			--->	FOTOTRAPPOLA LASER
							--->	A 			--->	FOTOTRAPPOLA ACUSTICA

			FINE			--->	°			--->	CARATTERE FINALE DELLA STRINGA


1.	CONFIGURAZIONE FILE BLUETOOTH SCATTO REMOTO

		8 CARATTERI 	--->	XX000000  	--->	COMANDO
						--->  	00XXXX00  	--->	VALORE TEMPO
						--->	000000X0	--->	UNITA' TEMPO 
						--->	0000000X	--->	FINE STRINGA
						
			COMANDI			--->	FF			---> 	MESSA A FUOCO
							--->	FFXXXXXX	--->	IMPOSTA TEMPO FUOCO + FUOCO
							--->	SS			--->	SCATTO
							--->	SSXXXXXX	--->	IMPOSTA TEMPO SCATTO + SCATTO
							---> 	FS			--->	FUOCO + SCATTO
							--->	DFXXXXXX	--->	IMPOSTA TEMPO DI FUOCO
							--->	DSXXXXXX	---> 	IMPOSTA TEMPO SCATTO
							
			UNITA' 			--->	m			--->	MILLISECONDI
							--->	S			--->	SECONDI
							--->	M			--->	MINUTI

			FINE			--->	*			--->	CARATTERE FINALE DELLA STRINGA


3.	CONFIGURAZIONE FILE BLUETOOTH FOTOTRAPPOLA LASER

		2 CARATTERI		--->	X0 			--->	MODALITA'
						--->	0X 			--->	FINE STRINGA

			FINE			--->	*			--->	CARATTERE FINALE DELLA STRINGA