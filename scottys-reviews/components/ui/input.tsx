import React from "react";

interface InputProps extends React.InputHTMLAttributes<HTMLInputElement> {}

export const Input: React.FC<InputProps> = (props) => {
  return (
    //cant seem to change the placeholder font to baloo2
    <input
       className="w-full max-w-3xl rounded-full px-6 py-4 
       text-lg focus:outline-none font-baloo2 placeholder:font-baloo2 focus:ring-2 focus:ring-blue-300"
      {...props}
    />
  );
};
