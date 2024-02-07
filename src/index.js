import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';

function Square(props) {
    return (
      <button className="square" onClick={props.onClick}>
        {props.value}
      </button>
    );
  }
  
  class Board extends React.Component {
    renderSquare(i) {
      return (
        <Square
          value={this.props.squares[i]}
          onClick={() => this.props.onClick(i)}
        />
      );
    }
  
    render() {
      return (
        <div>
          <div className="board-row">
            {this.renderSquare(0)}
            {this.renderSquare(1)}
            {this.renderSquare(2)}
          </div>
          <div className="board-row">
            {this.renderSquare(3)}
            {this.renderSquare(4)}
            {this.renderSquare(5)}
          </div>
          <div className="board-row">
            {this.renderSquare(6)}
            {this.renderSquare(7)}
            {this.renderSquare(8)}
          </div>
        </div>
      );
    }
  }
  
  class Game extends React.Component {
    constructor(props) {
      super(props);
      this.state = {
        history: [
          {
            squares: Array(9).fill(null)
          }
        ],
        stepNumber: 0,
        xIsNext: true,
        drop: -1
      };
    }
  
    handleClick(i) {
      const history = this.state.history.slice(0, this.state.stepNumber + 1);
      const current = history[history.length - 1];
      const squares = current.squares.slice();
      if (calculateWinner(squares)) {
        return;
      }
      if (this.state.stepNumber >= 6 &&this.state.drop===-1){
        if (squares[i]===(this.state.xIsNext ? "X":"O")){
            this.setState({
                drop:i
            });
            return;
        }else{
            return;
        }
      }
      if (this.state.drop!==-1){
        if( squares[i]===null &&chorusLapilli(i,this.state.drop)){

            squares[this.state.drop]=null;
            squares[i] = this.state.xIsNext ? "X" : "O";
            if( squares[4]===(this.state.xIsNext ? "X" : "O") &&i!==4){
                if (!calculateWinner(squares)) {
                    squares[this.state.drop]=this.state.xIsNext ? "X" : "O";
                    squares[i] =null;
                    this.setState({
                        drop:-1
                    });
                    return;
                } 
            }
            this.setState({
                drop:-1
            });
        }else{
            this.setState({
                drop:-1
            });
            return;
        }
      }
      
      if (this.state.stepNumber < 6){
        if (squares[i]){
            return;
        }else{
            squares[i] = this.state.xIsNext ? "X" : "O";
        }
      }
      this.setState({
        history: history.concat([
          {
            squares: squares
          }
        ]),
        stepNumber: history.length,
        xIsNext: !this.state.xIsNext
      });
    }
  
    jumpTo(step) {
      this.setState({
        stepNumber: step,
        xIsNext: (step % 2) === 0
      });
    }
  
    render() {
      const history = this.state.history;
      const current = history[this.state.stepNumber];
      const winner = calculateWinner(current.squares);
        /*
      const moves = history.map((step, move) => {
        const desc = move ?
          'Go to move #' + move :
          'Go to game start';
        return (
          <li key={move}>
            <button onClick={() => this.jumpTo(move)}>{desc}</button>
          </li>
        );
      });
      */
      let status;
      if (winner) {
        status = "Winner: " + winner;
      } else if(this.state.drop!==-1){
        status = "Next player: " + (this.state.xIsNext ? "X" : "O")+ " is moving piece";
      }
      else {
        status = "Next player: " + (this.state.xIsNext ? "X" : "O");
      }
  
      return (
        <div className="game">
          <div className="game-board">
            <Board
              squares={current.squares}
              onClick={i => this.handleClick(i)}
            />
          </div>
          <div className="game-info">
            <div>{status}</div>
             <ol>{/*moves*/}</ol>
          </div>
        </div>
      );
    }
  }
  
  // ========================================
  
  ReactDOM.render(<Game />, document.getElementById("root"));
  
  function calculateWinner(squares) {
    const lines = [
      [0, 1, 2],
      [3, 4, 5],
      [6, 7, 8],
      [0, 3, 6],
      [1, 4, 7],
      [2, 5, 8],
      [0, 4, 8],
      [2, 4, 6]
    ];
    for (let i = 0; i < lines.length; i++) {
      const [a, b, c] = lines[i];
      if (squares[a] && squares[a] === squares[b] && squares[a] === squares[c]) {
        return squares[a];
      }
    }
    return null;
  }
  function chorusLapilli(i,drop){
    let arr=[]
    switch (i){
        case 0:
            arr=[1,3,4]
            break;
        case 1:
            arr=[0,3,4,2,5]
            break;
        case 2:
            arr=[1,4,5]
            break;
        case 3:
            arr=[0,1,4,7,6]
            break;
        case 4:
            arr=[0,1,2,3,5,6,7,8]
            break;
        case 5:
            arr=[1,2,4,7,8]
            break;
        case 6:
            arr=[3,4,7]
            break;
        case 7:
            arr=[6,3,4,5,8]
            break;
        case 8:
            arr= [4,7,5]
            break;
        default:
            break;
    }
    return arr.includes(drop)
  }