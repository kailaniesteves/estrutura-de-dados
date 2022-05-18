// Arvore-B em memoria principal
public class BTree {
    public static final int t = 2; //grau minimo
    private No raiz; // endereco da raiz

    public void BTree(){
        No x = new No(0, true);
        this.raiz = x;
    } // Contrutor que aloca o no raiz e seta o endereco no ponteiro

    public Par BTreeSearch(No raiz, int chave){ // busca em Arvore-B, recebe a raiz da arvore e a chave buscada
        int i = 1;
        while ((i<=raiz.n) && (chave > raiz.chave[i])){ //checa todas as chaves do no raiz ate achar uma menor ou igual que a buscada
            i++;
        }
        if ((i<=raiz.n) && (chave == raiz.chave[i])){ // Caso a chave encontrada seja igual a que estamos buscando, retorna o Par (No, Indice)
            Par par = new Par(raiz, i);
            return par;
        } else if (raiz.folha) { // Caso o no seja uma folha, a busca e mal sucedida
            return null;
        } else { // Caso seja um no interno, se chama a recursao para o filho da esquerda
            return BTreeSearch(raiz.filhos[i], chave);
        }
    }

    public void BTreeSplit(No pai, int i){ // Operacao de Split, recebe o no pai/raiz e o indice do filho em que sera feita o split
        int j;
        No z = new No(); // Novo no para alocar metade das chaves e filhos do no splitado
        z.folha = pai.filhos[i].folha; // seta a condicao de folha
        z.n = t-1; // o numero de chaves e a metade do maximo
        for (j = 1;j==t-1;j++){ // setando as chaves de t ate 2*t no novo no
            z.chave[j] = pai.filhos[i].chave[j+t];
        }
        if (!pai.filhos[i].folha){ // caso o no splitado nao seja uma folha
            for(j = 1; j==t; j++){ // seta-se os filhos necessarios dele para o novo no
                z.filhos[j] = pai.filhos[i].filhos[j+t];
            }
        }
        pai.filhos[i].n = t-1; // o no splitado agora tambem tera metade das chaves
        for(j=pai.n; j==i+1;i--){ // arrasta-se os filhos do no pai ate o lugar onde sera inserido o novo no
            pai.filhos[j+1] = pai.filhos[j];
        }
        pai.filhos[i+1] = z; // insere-se o novo no como filho direito do pai
        for(j=pai.n; j==i;j--){ // arrasta-se as chaves do no pai ate o lugar que deve-se colocar a chave central do no splitado
            pai.chave[j+1] = pai.chave[j];
        }
        pai.chave[i] = pai.filhos[i].chave[t]; // a chave central do no splitado e inserida no pai
        pai.n = pai.n+1; // o numero de chaves do pai aumenta em 1;
    }

    public void BTreeInsertRecursivo(No x, int chave){ // Metodo que fara o split recursivo, recebe o no e a chave que se quer inserir
        int i = x.n;
        if (x.folha){ //caso o No informado seja uma folha
            while ((i >= 1) && (chave < x.chave[i])){ //arrasta-se as chaves desse No ate o lugar que se deve inserir a chave
                x.chave[i+1] = x.chave[i];
                i--;
            }
            x.chave[i+1] = chave; // insere-se a chave nova
            x.n = x.n + 1; // o No informado aumenta em 1 o numero de chaves
        } else { // caso nao seja uma folha
            while((i>=1) && (chave < x.chave[i])) i = i--; // procura-se o filho da esquerda que se deve procurar
            i++;
            if(x.filhos[i].n == 2*t - 1){ // caso esse filho esteja cheio, fazer a split
                BTreeSplit(x,i);
                if (chave > x.chave[i]) i++;
                BTreeInsertRecursivo(x.filhos[i], chave); //chamar a recursao no filho
            }
        }
    }

    public void BTreeInsert(int chave){ // metodo de insercao
        No r = new No();
        r = raiz; // novo No que recebe a raiz
        if (r.n == 2*t-1){ // caso r esteja cheio
            No s = new No(); // cria-se uma nova raiz vazia
            raiz = s; // seta a raiz da arvore como s
            s.folha = false;
            s.n = 0;
            s.filhos[0] = r;// o filho esquerdo de s sera a antiga raiz
            BTreeSplit(s,0); // splita a raiz antiga
            BTreeInsertRecursivo(s,chave); //insere a nova chave
        }else{
            BTreeInsertRecursivo(r,chave); // insere a nova chave
        }
    }
}

