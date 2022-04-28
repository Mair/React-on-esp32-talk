import { useEffect, useState } from "preact/hooks";

export function PushButton() {
  const [count, setCount] = useState<number>(0);
  const [btnPressed, setBtnPressed] = useState<boolean>(false);

  useEffect(() => {
    var socket = new WebSocket("ws://my-esp32.local/ws-api/btn-push");
    socket.onopen = () => socket.send("ready for button press");

    socket.onmessage = (event) => {
      console.log(event.data);
      const data = JSON.parse(event.data);
      setBtnPressed(data.btn_state);
      setCount((c) => (c++ > 99 ? 0 : c));
    };
    return () => {
      socket.send(JSON.stringify({ cmd: "stop" }));
    };
  }, []);

  return (
    <>
      <span class="countdown font-mono text-6xl">
        <span style={`--value:${count};`} />
      </span>

      <div class="alert alert-info shadow-lg w-32">
        <div>
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" class="stroke-current flex-shrink-0 w-6 h-6">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M13 16h-1v-4h-1m1-4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z" />
          </svg>
          <span>{btnPressed ? "pressed" : "released"}</span>
        </div>
      </div>
    </>
  );
}
