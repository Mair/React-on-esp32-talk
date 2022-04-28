import { useCallback, useEffect, useMemo, useState } from "preact/hooks";
import debounce from "lodash.debounce";

export const Servo = () => {
  const [angle, setAngle] = useState(0);
  var socket = useMemo(() => new WebSocket("ws://my-esp32.local/ws-api/servo"), []);

  useEffect(() => {
    socket.onopen = () => socket.send(JSON.stringify({ angle: 0 }));
    return () => {
      socket.send(JSON.stringify({ angle: 0 }));
    };
  }, []);

  const onSlide = (value: number) => {
    setAngle(value);
    console.log(value);
    socket.send(JSON.stringify({ angle }));
  };

  //const debounceOnSlide = debounce((value) => onSlide(value), 500);

  return (
    <>
      <svg transform={`rotate(${(angle + 270) * -1})`} xmlns="http://www.w3.org/2000/svg" className="h-20 w-20" fill="none" viewBox="0 0 24 24" stroke="currentColor" strokeWidth={2}>
        <path strokeLinecap="round" strokeLinejoin="round" d="M8 7l4-4m0 0l4 4m-4-4v18" />
      </svg>
      <input type="range" min="0" max="180" value={angle} class="range range-accent w-96" onChange={(e: any) => onSlide(Number(e.target.value))}></input>
    </>
  );
};
