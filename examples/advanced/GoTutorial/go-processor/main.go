package main

import (
	"bytes"
	"flag"
	"io"
	"log"

	"github.com/go-mangos/mangos"
	"github.com/go-mangos/mangos/protocol/pull"
	"github.com/go-mangos/mangos/protocol/push"
	"github.com/go-mangos/mangos/transport/ipc"
	"github.com/go-mangos/mangos/transport/tcp"
)

func main() {
	var iaddr string
	flag.StringVar(&iaddr, "iaddr", "tcp://localhost:5555", "input data port")

	var oaddr string
	flag.StringVar(&oaddr, "oaddr", "tcp://localhost:5556", "output data port")

	flag.Parse()

	isck, err := pull.NewSocket()
	if err != nil {
		log.Fatalf("error creating a nanomsg socket: %v\n", err)
	}
	defer isck.Close()

	isck.AddTransport(ipc.NewTransport())
	isck.AddTransport(tcp.NewTransport())

	osck, err := push.NewSocket()
	if err != nil {
		log.Fatalf("error creating output port: %v\n", err)
	}
	defer osck.Close()

	osck.AddTransport(ipc.NewTransport())
	osck.AddTransport(tcp.NewTransport())

	log.Printf("dialing %s ...\n", iaddr)
	err = isck.Dial(iaddr)
	if err != nil {
		log.Fatalf("error dialing: %v\n", err)
	}
	log.Printf("dialing %s ... [done]\n", iaddr)

	log.Printf("dialing %s ...\n", oaddr)
	err = osck.Dial(oaddr)
	if err != nil {
		log.Fatalf("error dialing: %v\n", err)
	}
	log.Printf("dialing %s ... [done]\n", oaddr)

	for {
		msg, err := isck.Recv()
		if err != nil {
			if err == io.EOF || err == mangos.ErrClosed {
				log.Printf("received EOF: %v\n", err)
				break
			}
			log.Fatalf("error receiving data: %v\n", err)
		}
		log.Printf("recv: %v\n", string(msg))

		omsg := bytes.Repeat(msg, 2)
		err = osck.Send(omsg)
		if err != nil {
			log.Fatalf("error sending data: %v\n", err)
		}
	}

}
