import { useState } from "preact/hooks";

export const Led = () => {
  const [isOn, setIsOn] = useState(false);

  const onClick = async () => {
    let is_on = !isOn;
    await fetch("/api/toggle-led", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ is_on }),
    });
    setIsOn(is_on);
  };

  return <div class={`w-48 h-48 border-8 border-black rounded-full ${isOn ? "bg-blue-600" : ""}`} onClick={onClick} />;
};
