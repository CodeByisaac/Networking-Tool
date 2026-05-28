#!/usr/bin/env python3
"""Connect N TCP clients, send messages, then disconnect. To stress ThreadSanitizer."""
import argparse
import socket
import threading
import time


def client(client_id: int, host: str, port: int, messages: int) -> None:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((host, port))
    for i in range(messages):
        sock.sendall(f"hello from client {client_id} msg {i}\n".encode())
        time.sleep(0.02)
    sock.close()


def main() -> None:
    p = argparse.ArgumentParser()
    p.add_argument("-n", "--clients", type=int, default=10)
    p.add_argument("--host", default="127.0.0.1")
    p.add_argument("--port", type=int, default=8080)
    p.add_argument("--messages", type=int, default=20, help="messages per client")
    args = p.parse_args()

    threads = [
        threading.Thread(target=client, args=(i, args.host, args.port, args.messages))
        for i in range(args.clients)
    ]
    for t in threads:
        t.start()
    for t in threads:
        t.join()
    print(f"Done: {args.clients} clients sent {args.messages} messages each.")


if __name__ == "__main__":
    main()
