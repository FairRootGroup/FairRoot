// Copyright 2016 The fer Authors.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package main

import (
	"log"

	"github.com/sbinet-alice/fer"
	"github.com/sbinet-alice/fer/config"
)

type sink struct {
	cfg   config.Device
	datac chan fer.Msg
}

func (dev *sink) Configure(cfg config.Device) error {
	dev.cfg = cfg
	return nil
}

func (dev *sink) Init(ctl fer.Controler) error {
	datac, err := ctl.Chan("data", 0)
	if err != nil {
		return err
	}

	dev.datac = datac
	return nil
}

func (dev *sink) Run(ctl fer.Controler) error {
	for {
		select {
		case data := <-dev.datac:
			ctl.Printf("received: %q\n", string(data.Data))
		case <-ctl.Done():
			return nil
		}
	}
}

func (dev *sink) Pause(ctl fer.Controler) error {
	return nil
}

func (dev *sink) Reset(ctl fer.Controler) error {
	return nil
}

func main() {
	err := fer.Main(&sink{})
	if err != nil {
		log.Fatal(err)
	}
}
