import React from "react";

interface TextareaProps
  extends React.TextareaHTMLAttributes<HTMLTextAreaElement> {}

export const Textarea: React.FC<TextareaProps> = (props) => {
  return (
    <textarea
      className="w-full border rounded px-3 py-2 focus:outline-none focus:ring-2 focus:ring-blue-300"
      {...props}
    />
  );
};
