:-use_module(library(sockets)).

port(60001).

server:-
	port(Port),
	socket_server_open(Port,Socket),
	socket_server_accept(Socket, _Client, Stream, [type(text)]),
	server_loop(Stream),
	socket_server_close(Socket),
	write('Server Exit'),nl.

server_loop(Stream) :-
	repeat,
		read(Stream, ClientRequest),
		write('Received: '), write(ClientRequest), nl, 
		server_input(ClientRequest, ServerReply),
		format(Stream, '~q.~n', [ServerReply]),
		write('Send: '), write(ServerReply), nl, 
		flush_output(Stream),
	(ClientRequest == bye; ClientRequest == end_of_file), !.

server_input(initialize, ok(Board)):- 
	initialize(Board), !.

server_input(execute(primeiraJogada, Col, Lin, Board), ok(NewBoard)):- 
	primeiraJogada(Col,Lin),
	alteraTab(1,0,Col,Lin,Board,NewBoard), !.

server_input(execute(primeiraJogada, Col2, Lin2, Col1, Lin1, Board), ok(NewBoard)):-
	getElem(Col1,Lin1,Elem,Board),
	Elem =:= 0,
	adjacente(Col1,Lin1,Col2,Lin2,_),
	alteraTab(2,0,Col2,Lin2,Board,NewBoard), !.

server_input(execute(jogada, 1, Col, Lin, ColDest, LinDest, Board), ok(NewBoard)):- 
	verificaJogada(Col,Lin,ColDest,LinDest,1,Board,_,NewBoard), !.

server_input(execute(jogada, 2, Col, Lin, ColDest, LinDest, Board), ok(NewBoard)):- 
	verificaJogada(Col,Lin,ColDest,LinDest,2,Board,_,NewBoard), !.

server_input(avalia(Jogador,Board),ok(Result)):-
	avaliaTab(1,1,Jogador,Board)->Result=1;Result=0,!.

server_input(bye, ok):-!.
server_input(end_of_file, ok):-!.
server_input(_, invalid) :- !.


%%% Jogo %%%

:-use_module(library(lists)).
:-use_module(library(random)).

initialize([[1,2,1,2,1,2,1,2],[2,1,2,1,2,1,2,1],[1,2,1,2,1,2,1,2],[2,1,2,1,2,1,2,1],[1,2,1,2,1,2,1,2],[2,1,2,1,2,1,2,1],[1,2,1,2,1,2,1,2],[2,1,2,1,2,1,2,1]]).


primeiraJogada(1,1).
primeiraJogada(4,4).
primeiraJogada(5,5).
primeiraJogada(8,8).

opValida(1).
opValida(2).

selec_jogadores(Opcao):-
	write('Selecione o modo de jogo pretendido'),nl,
	write('1- Humano vs PC'),nl,
	write('2- Humano vs Humano'), nl,
	read(Op),
	(opValida(Op)->
		Opcao is Op;
		write('Opcao invalida'),nl,selec_jogadores(Opcao)).

%%%%%%%%%%%%%%%%%%%%%%%%%%% Predicados de remoção de peças iniciais, caso o modo de jogo seja humano contra humano %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	

pede_retirar_pecasJog1(Tab):-						%%%%%%%% Pedir ao primeiro jogador para retirar a primeira peça %%%%%%%%%%%%%%%%%%
	write('Jogador 1, retire a primeira peca'),nl,
	write('Coluna: '),nl,
	read(C),
	Col is C,
	write('Linha: '),nl,
	read(L),
	Lin is L,
	(posValidaRetirarJog1(Col,Lin) -> retira_pecas(Tab,Col,Lin,1);
	 write('Posicao nao valida, selecione uma das pecas do centro ou dos cantos.'),nl,
	 pede_retirar_pecasJog1(Tab)).

pede_retirar_pecasJog2(Tab,ColR,LinR):-  			%%%%%%%%%% Pedir ao segundo jogador para retirar a segunda peça %%%%%%%%%%%%
	write('Jogador 2, retire uma peca'),nl,
	write('Coluna: '),nl,
	read(C),
	Col is C,
	write('Linha: '),nl,
	read(L),
	Lin is L,
	(adjacente(ColR,LinR,Col,Lin,_) -> retira_pecas(Tab,Col,Lin,2);
	 write('Posicao nao valida, selecione uma peca adjacente a posicao vazia.'),nl,
	 pede_retirar_pecasJog2(Tab,ColR,LinR)).

retira_pecas(Tab,Col,Lin,J):-					
	alteraTab(J,0,Col,Lin,Tab,TabAux),
	(J=:=1->imprimeTabuleiro(TabAux),pede_retirar_pecasJog2(TabAux,Col,Lin);
		jogar(TabAux,1,0)).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Operações de remoção de peças iniciais, caso o modo de jogo seja humano contra computador %%%%%%%%%%%%%%%%


hum_retira_pecas(Tab):-  %%%%% pede ao jogador humano para retirar a primeira peça %%%%%%%%%%%%%%
	write('Jogador humano, retire a primeira peca'),nl,
	write('Coluna: '),nl,
	read(C),
	Col is C,
	write('Linha: '),nl,
	read(L),
	Lin is L,
	(posValidaRetirarJog1(Col,Lin) -> retira_pecas2(Tab,Col,Lin,1);
	 write('Posicao nao valida, selecione uma das pecas do centro ou dos cantos.'),nl,
	 hum_retira_pecas(Tab)).

retira_pecas2(Tab,Col,Lin,J):-
	alteraTab(J,0,Col,Lin,Tab,TabAux),
	(J=:=1->imprimeTabuleiro(TabAux),write('O Computador adversario vai retirar uma peca'),nl,pc_retira_pecas(TabAux,Col,Lin);
		jogar(TabAux,1,1)).

pc_retira_pecas(Tab,ColR,LinR):-
	random(1,9,Col),
	random(1,9,Lin),
	(adjacente(ColR,LinR,Col,Lin,_)->
		retira_pecas2(Tab,Col,Lin,2);
		pc_retira_pecas(Tab,ColR,LinR)).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

jogar(Tab,Jogador,CPU):-
	imprimeTabuleiro(Tab),
	write('Jogador '),write(Jogador),write(' e a sua vez de jogar'),nl,
	(Jogador=:=1->pedeJogada(1,Tab,CPU);
		pedeJogada(2,Tab,CPU)).


%%%%%%%%%%%% Operações sobre listas %%%%%%%%%%%%%%%%
alteraTab(Elem,ElemNovo,Col,Lin,Tab,TabNovo):-
	(Col=:=Lin->
		alteraTabAux1(1,Elem,ElemNovo,Col,Lin,Tab,TabNovo),!;
		alteraTabAux2(1,Elem,ElemNovo,Col,Lin,Tab,TabNovo),!).

alteraTabAux1(_,_,_,_,_,[],[]).
alteraTabAux1(Lin,Elem,ElemNovo,Col,Lin,[Linha|Resto],[LinhaNova|RestoNovo]):-
	alteraLinha1(1,Elem,ElemNovo,Col,Linha,LinhaNova),
	N2 is Lin+1,
	alteraTabAux1(N2,Elem,ElemNovo,Col,Lin,Resto,RestoNovo).
alteraTabAux1(N,Elem,ElemNovo,Col,Lin,[Linha|Resto],[Linha|RestoNovo]):-
	 N2 is N+1,
	alteraTabAux1(N2,Elem,ElemNovo,Col,Lin,Resto,RestoNovo).

alteraLinha1(_,_,_,_,[],[]).
alteraLinha1(Col,Elem,ElemNovo,Col,[Elem|Resto],[ElemNovo|RestoNovo]):-
	N2 is Col+1,
	alteraLinha1(N2,Elem,ElemNovo,Col,Resto,RestoNovo).
alteraLinha1(N,Elem,ElemNovo,Col,[El|Resto],[El|RestoNovo]):-
	N2 is N+1,
	alteraLinha1(N2,Elem,ElemNovo,Col,Resto,RestoNovo).


alteraTabAux2(_,_,_,_,_,[],[]).
alteraTabAux2(Lin,Elem,ElemNovo,Col,Lin,[Linha|Resto],[LinhaNova|RestoNovo]):-
	alteraLinha2(1,Elem,ElemNovo,Col,Linha,LinhaNova),
	N2 is Lin+1,
	alteraTabAux2(N2,Elem,ElemNovo,Col,Lin,Resto,RestoNovo).
alteraTabAux2(N,Elem,ElemNovo,Col,Lin,[Linha|Resto],[Linha|RestoNovo]):-
	N\=Lin,
	 N2 is N+1,
	alteraTabAux2(N2,Elem,ElemNovo,Col,Lin,Resto,RestoNovo).

alteraLinha2(_,_,_,_,[],[]).
alteraLinha2(Col,Elem,ElemNovo,Col,[Elem|Resto],[ElemNovo|RestoNovo]):-
	N2 is Col+1,
	alteraLinha2(N2,Elem,ElemNovo,Col,Resto,RestoNovo).
alteraLinha2(N,Elem,ElemNovo,Col,[El|Resto],[El|RestoNovo]):-
	N\=Col, 
	N2 is N+1,
	alteraLinha2(N2,Elem,ElemNovo,Col,Resto,RestoNovo).

getElem(Col0,Lin0,Elem,Tab) :-
   Lin is Lin0-1,
   Col is Col0-1, 
   nth0(Lin,Tab,RowList),
   nth0(Col,RowList,Elem).

%%%%%%%%%%%%%%%%%%%% Operações de validade e execução de jogadas %%%%%%%%%%%%%%

mesmaPos(Col1,Lin1,Col2,Lin2):-  %%%% verifica se as posicoes sao iguais
	Col1=:=Col2,
	Lin1=:=Lin2.

direcaoInvalida(Col1,Lin1,Col2,Lin2):-  %%% verifica se a direcção da jogada não é diagonal
	Col1=\=Col2,
	Lin1=\=Lin2.

verificaComePecaAux(Col1,Lin1,Col2,Lin2,Jogador,Tab,Elem,ColR,LinR,CPU,TabNovo):-			%%%% Verifica se a posição entre as posições origem e destino nao contem uma peça do jogador que está a jogar, isto é, o jogador não pode capturar a sua própria peça
	Elem=\=Jogador , verificaComePecaAux2(Col1,Lin1,Col2,Lin2,Jogador,Tab,Elem,ColR,LinR,CPU,TabNovo).

verificaComePecaAux2(Col1,Lin1,Col2,Lin2,Jogador,Tab,Elem,ColR,LinR,CPU,TabNovo):-  %%%% Verifica se a posição entre origem e destino não é um espaço vazio, todas as jogadas têm de capturar uma peça
	Elem=\=0,
	alteraTab(Elem,0,ColR,LinR,Tab,TabNovo),
	executaJogada(Col1,Lin1,Col2,Lin2,Jogador,TabNovo,CPU).

verificaComePeca(Col1,Lin1,Col2,Lin2,Jogador,Tab,CPU,TabNovo):-    %%%% Calcula a posição da peça entre a posição origem e destino
	(Col1=:=Col2 -> ColR is Col1; LinR is Lin1),
	(Col1>Col2 -> ColR is Col1-1; UN is Col1),
	(Col1<Col2 -> ColR is Col2-1; UN is Col1),
	(Lin1>Lin2 -> LinR is Lin1-1; UN is Col1),
	(Lin1<Lin2 -> LinR is Lin2-1; UN is Col1),
	getElem(ColR,LinR,PosM,Tab),
	getElem(Col1,Lin1,PosO,Tab),
	getElem(Col2,Lin2,PosD,Tab),
	PosMeio is PosM,
	PosOri is PosO,
	PosDes is PosD,
	(Jogador=:=1 -> Adv is 2;Adv is 1),
	PosMeio==Adv,PosOri==Jogador,PosDes==0,
	verificaComePecaAux(Col1,Lin1,Col2,Lin2,Jogador,Tab,PosM,ColR,LinR,CPU,TabNovo).


verificaJogada(Col1,Lin1,Col2,Lin2,Jogador,Tab,CPU,TabNovo):-
	(Col1=:=Col2 -> Dist is abs(Lin1-Lin2); Dist is abs(Col1-Col2)),       %%%% Calcula distancia entre duas posições
	Dist=:=2, verificaComePeca(Col1,Lin1,Col2,Lin2,Jogador,Tab,CPU,TabNovo).

executaJogadaAux2(_,_,ColDestino,LinDestino,Jogador,TabNovo,CPU):-  %%%% Modifica a posição de destino para conter a peça do jogador a efetuar a jogada, e troca o turno.
	getElem(ColDestino,LinDestino,Elem,TabNovo),
	alteraTab(Elem,Jogador,ColDestino,LinDestino,TabNovo,TabAux).
	

executaJogadaAux(ColOrigem,LinOrigem,ColDestino,LinDestino,Jogador,Tab,CPU):-  %%%%% Modifica a posição de origem e verifica se a posição de destino é um espaço vazio, ou seja, preenchido com 0
	getElem(ColDestino,LinDestino,Elem,Tab),
	Elem=:=0, alteraTab(Jogador,0,ColOrigem,LinOrigem,Tab,TabNovo), executaJogadaAux2(ColOrigem,LinOrigem,ColDestino,LinDestino,Jogador,TabNovo,CPU).

executaJogada(ColOrigem,LinOrigem,ColDestino,LinDestino,Jogador,Tab,CPU):-  %%%%%% Verifica se a posição de origem contém uma peça que pertence ao jogador a realizar a jogada
	getElem(ColOrigem,LinOrigem,Val,Tab),
	Val=:=Jogador,
	executaJogadaAux(ColOrigem,LinOrigem,ColDestino,LinDestino,Jogador,Tab,CPU).

testaJogada(ColOrigem,LinOrigem,ColDestino,LinDestino,Jogador,Tab,CPU):-  %%%%% começa a verificar se a jogada é valida. É utilizado um conjunto de predicados para avaliar a jogada
	(direcaoInvalida(ColOrigem,LinOrigem,ColDestino,LinDestino)-> pedeJogada(Jogador,Tab,CPU);
	verificaJogada(ColOrigem,LinOrigem,ColDestino,LinDestino,Jogador,Tab,CPU)).


validaPedido(ColOrigem,LinOrigem,ColDestino,LinDestino,Jogador,Tab,CPU):- %%%%%%%% Começa por verificar se as posições de origem e destino são as mesmas, se não, continua com a avaliação da validade da jogada
	(mesmaPos(ColOrigem,LinOrigem,ColDestino,LinDestino)-> pedeJogada(Jogador,Tab,CPU);
														testaJogada(ColOrigem,LinOrigem,ColDestino,LinDestino,Jogador,Tab,CPU)).
														
pedeJogada(Jogador,Tab,CPU):-
	(CPU=:=0 ->						%%%%%%%%%% Primeiro avalia o tabuleiro para verificar se o jogador actual tem jogadas possíveis. Se tiver, são-lhes pedidas as 
		(avaliaTab(1,1,Jogador,Tab)->	%%%%%%%%%% posições de origem e destino da sua jogada, e avalia depois a validade da jogada.
			write('Coluna de origem: '),
			read(CO),nl, ColOrigem is CO,
			write('Linha de origem: '),
			read(LO),nl, LinOrigem is LO,
			write('Coluna de destino: '),
			read(CD),nl, ColDestino is CD,
			write('Linha de destino: '),
			read(LD),nl, LinDestino is LD,
			(validaPosicoes(ColOrigem,LinOrigem,ColDestino,LinDestino)->
				validaPedido(ColOrigem,LinOrigem,ColDestino,LinDestino,Jogador,Tab,CPU);
				write('Posicoes nao validas'),nl,pedeJogada(Jogador,Tab,CPU));write('Nao ha jogadas possiveis, o jogador '),write(Jogador),write(' perdeu'));
		(Jogador=:=1 ->
			(avaliaTab(1,1,Jogador,Tab)->
				write('Coluna de origem: '),
				read(CO),nl, ColOrigem is CO,
				write('Linha de origem: '),
				read(LO),nl, LinOrigem is LO,
				write('Coluna de destino: '),
				read(CD),nl, ColDestino is CD,
				write('Linha de destino: '),
				read(LD),nl, LinDestino is LD,
				(validaPosicoes(ColOrigem,LinOrigem,ColDestino,LinDestino)->
					validaPedido(ColOrigem,LinOrigem,ColDestino,LinDestino,Jogador,Tab,CPU);
					write('Posicoes nao validas'),nl,pedeJogada(Jogador,Tab,CPU));write('Nao ha jogadas possiveis, o jogador humano perdeu'));
			(avaliaTab(1,1,Jogador,Tab)->
				random(1,9,ColOrigem),
				random(1,9,LinOrigem),
				random(1,9,ColDestino),
				random(1,9,LinDestino),
				validaPedido(ColOrigem,LinOrigem,ColDestino,LinDestino,Jogador,Tab,CPU);
				write('Nao ha jogadas possiveis, o computador perdeu')))).




avaliaTab(Col,Lin,Jogador,Tab):-										%%%
	(Lin<9->															%%%
		(avaliaAux(Col,Lin,Jogador,Tab)->!;								%%%
		LinN is Lin+1,													%%%		Estes predicados servem para percorrer o tabuleiro à procura de uma peça
		avaliaTab(Col,LinN,Jogador,Tab));fail).					    	%%%		do jogador, e verificar se é possivel fazer jogadas através dessa peça
																		%%%
avaliaAux(Col,Lin,Jogador,Tab):-										%%%
	(Col<9->															%%%
		(jogadaValida(Col,Lin,Jogador,Tab)->!;							%%%
		ColN is Col+1,													%%%
		avaliaAux(ColN,Lin,Jogador,Tab));fail).							%%%
																		%%%

jogadaValida(Col,Lin,Jogador,Tab):-										%%%%%   Ao encontrar uma posição com a peça do jogador actual,
	getElem(Col,Lin,Elem,Tab),											%%%%%   são usados vários predicados para verificar se há jogadas possíveis
	(Jogador=:=Elem->
		(checkDir(Col,Lin,Jogador,Tab)->!;
			(checkEsq(Col,Lin,Jogador,Tab)->!;
				(checkCima(Col,Lin,Jogador,Tab)->!;
					(checkBaixo(Col,Lin,Jogador,Tab)->!;fail))));fail).



checkDir(Col,Lin,Jogador,Tab):-		%%%%% Verifica, ao encontrar uma peça do jogador actual, se é possível jogar para a direita dessa peça
		ColD is Col+1,
		getElem(ColD,Lin,ElemD,Tab),
		ElemD=\=0,
		ElemD=\=Jogador,
		ColD1 is ColD+1,
		getElem(ColD1,Lin,ElemD1,Tab),
		ElemD1=:=0.

checkEsq(Col,Lin,Jogador,Tab):-		%%%%% Verifica, ao encontrar uma peça do jogador actual, se é possível jogar para a esquerda dessa peça
		ColE is Col-1,
		getElem(ColE,Lin,ElemE,Tab),
		ElemE=\=0,
		ElemE=\=Jogador,
		ColE1 is ColE-1,
		getElem(ColE1,Lin,ElemE1,Tab),
		ElemE1=:=0.

checkCima(Col,Lin,Jogador,Tab):-	%%%%% Verifica, ao encontrar uma peça do jogador actual, se é possível jogar para cima dessa peça
		LinC is Lin-1,
		getElem(Col,LinC,ElemC,Tab),
		ElemC=\=0,
		ElemC=\=Jogador,
		LinC1 is LinC-1,
		getElem(Col,LinC1,ElemC1,Tab),
		ElemC1=:=0.

checkBaixo(Col,Lin,Jogador,Tab):-  %%%%% Verifica, ao encontrar uma peça do jogador actual, se é possível jogar para baixo dessa peça
		LinB is Lin+1,
		getElem(Col,LinB,ElemB,Tab),
		ElemB=\=0,
		ElemB=\=Jogador,
		LinB1 is LinB+1,
		getElem(Col,LinB1,ElemB1,Tab),
		ElemB1=:=0.

validaPosicoes(Col1,Lin1,Col2,Lin2):- %%%%% Verifica se as coordenadas introduzidas pertencem ao tabuleiro
	member(Col1,[1,2,3,4,5,6,7,8]),
	member(Lin1,[1,2,3,4,5,6,7,8]),
	member(Col2,[1,2,3,4,5,6,7,8]),
	member(Lin2,[1,2,3,4,5,6,7,8]).

%%%%%% Operações sobre o tabuleiro %%%%%%%

pertenceLim(Col,Lin):-member(Col,Tab),member(Lin,Tab).   %%% ver se posiçao pertence ao tabuleiro


  %% direções, c-cima,b-baixo,e-esquerda,d-direita
direccao((c),0, 1).
direccao((b),0,-1).
direccao((e),-1,0).
direccao((d),1,0).

 %%% Verifica se duas posições são adjacentes
adjacente(Col1,Lin1,Col2,Lin2,(c)):- Col2=:=Col1, Lin2=:=Lin1+1, pertenceLim(Col2,Lin2).
adjacente(Col1,Lin1,Col2,Lin2,(b)):- Col2=:=Col1, Lin2=:=Lin1-1, pertenceLim(Col2,Lin2).
adjacente(Col1,Lin1,Col2,Lin2,(e)):- Col2=:=Col1-1, Lin2=:=Lin1, pertenceLim(Col2,Lin2).
adjacente(Col1,Lin1,Col2,Lin2,(d)):- Col2=:=Col1+1, Lin2=:=Lin1, pertenceLim(Col2,Lin2).








