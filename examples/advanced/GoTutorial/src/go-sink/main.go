package main

import (
	"flag"
	"io"
	"log"

	"github.com/go-mangos/mangos"
	"github.com/go-mangos/mangos/protocol/pull"
	"github.com/go-mangos/mangos/transport/ipc"
	"github.com/go-mangos/mangos/transport/tcp"
)

func main() {
	var addr string
	flag.StringVar(&addr, "addr", "tcp://localhost:5555", "input data port")

	flag.Parse()

	sck, err := pull.NewSocket()
	if err != nil {
		log.Fatalf("error creating a nanomsg socket: %v\n", err)
	}
	defer sck.Close()

	sck.AddTransport(ipc.NewTransport())
	sck.AddTransport(tcp.NewTransport())

	log.Printf("dialing %s ...\n", addr)
	err = sck.Dial(addr)
	if err != nil {
		log.Fatalf("error dialing: %v\n", err)
	}
	log.Printf("dialing %s ... [done]\n", addr)

	for {
		msg, err := sck.Recv()
		if err != nil {
			if err == io.EOF || err == mangos.ErrClosed {
				log.Printf("received EOF: %v\n", err)
				break
			}
			log.Fatalf("error receiving from bus: %v\n", err)
		}
		log.Printf("recv: %v\n", string(msg))
	}

}
